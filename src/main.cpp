#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <variant>

#include "njordx.hpp"
#include "company.tpp"
#include "person.tpp"

using Variant = std::variant<std::shared_ptr<Person>, std::shared_ptr<Company>>;

// Function prototypes
void handleBuy(const Variant user, const std::string& stock, int quantity, double price);
void handleSell(const Variant user, const std::string& stock, int quatity, double price);
void handleOrder(const Variant user, const std::string& stock, int quatity, double price, std::string orderType);

void handleAvailable(const Variant user);
void handleInfo(Variant user);
void handleCreate(const Variant user, const std::string symbol, const int num);
void displayHelp();

int main(int argc, char* argv[]) {
    try {
        if (argc < 5) {
            throw std::invalid_argument("No command provided. Use 'person' or 'company' and provide name, reg. number and balance.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Create exchange
    Njordx* exchange = new Njordx();
    
    std::string user_tp = std::move(argv[1]);
    std::string name = std::move(argv[2]);
    std::string reg_number = std::move(argv[3]);
    int balance = 0;
    try {
        balance = std::stoi(argv[4]);
    } catch (const std::invalid_argument&) {
        std::cerr << "Error: Invalid balance. Please provide a number.\n";
        return 1;
    } catch (const std::out_of_range&) {
        std::cerr << "Error: Balance out of range. Please use a smaller value.\n";
        return 1;
    }

    // User er en variant, sombåde kan være en person eller en company
    // Not really useful as we only define it once, but it's a good example of how to use std::variant
    Variant user;

    if (user_tp == "person") {
        user = std::make_shared<Person>(1, balance, exchange, name, reg_number);
        // std::cout << "Creating a new person with name: " << name << " and reg. number: " << reg_number << "\n";
    } else if (user_tp == "company") {
        // std::cout << "Creating a new company with name: " << name << " and reg. number: " << reg_number << "\n";
        user = std::make_shared<Company>(1, balance, exchange, name, reg_number);
    } else {
        std::cerr << "Error: Unknown user type. Use 'person' or 'company'.\n";
        return 1;
    }

    std::string input;
    std::cout << "Welcome to the NJORDX trading platform! Type 'help' for a list of commands.\n";

    while (true) {
        // Prompt user
        std::cout << "> ";
        std::getline(std::cin, input);

        // Exit the loop if user inputs "exit"
        if (input == "exit") {
            std::cout << "Goodbye!\n";
            break;
        }

        try {
            // Parse the command and arguments
            std::istringstream iss(input);
            std::string command;
            iss >> command;

            if (command == "buy" || command == "sell") {
                std::string stock, quantity_t, price_t;
                iss >> stock;
                if (stock.empty()) {
                    throw std::invalid_argument("Usage: buy <stock>");
                }
                int quantity;
                iss >> quantity_t;
                try {
                    quantity = stoi(quantity_t);
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid quantity. Please provide a number.\n";
                    return 1;
                } catch (const std::out_of_range&) {
                    std::cerr << "Error: Quantity out of range. Please use a smaller value.\n";
                    return 1;
                }
                double price;
                iss >> price_t;
                try {
                    price = stod(price_t);
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid price. Please provide a number.\n";
                    return 1;
                } catch (const std::out_of_range&) {
                    std::cerr << "Error: Price out of range. Please use a smaller value.\n";
                    return 1;
                }

                handleOrder(user, stock, quantity, price, command);
            
            } else if (command == "info") {
                handleInfo(user);
            } else if (command == "available") {
                handleAvailable(user);
            } else if (command == "help") {
                displayHelp();
            } else if (command == "create") { 
                std::string sym, quant_t;
                int quant;
                iss >> sym;
                iss >> quant_t;
                if (sym.empty() || quant_t.empty()) {
                    throw std::invalid_argument("Usage: create <name> <quantity>");
                }
                try {
                    quant = stoi(quant_t);
                } catch (const std::invalid_argument&) {
                    std::cerr << "Error: Invalid balance. Please provide a number.\n";
                    return 1;
                } catch (const std::out_of_range&) {
                    std::cerr << "Error: Balance out of range. Please use a smaller value.\n";
                    return 1;
                }
                handleCreate(user, sym, quant);
            } else {
                throw std::invalid_argument("Unknown command: " + command + ". Type 'help' for a list of commands.");
            }
            // Create bogus buy order so stocks can be sold
            handleBuy(user, "aapl", 10, 100.0);
            exchange->displayOrderBook(OrderType::BUY);
            exchange->displayOrderBook(OrderType::SELL);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}

// bool Trader<Derived>::placeOrder(const Stock& stock, const OrderType order_tp, int quantity, double price)
void handleBuy(const Variant user, const std::string& stock, int quantity, double price) {
     std::visit([&](auto&& user) {
        // Check if excange is nullptr
        if (user->exchange == nullptr) {
            std::cerr << "User has not joined an exchange\n";
            return;
        }
        // Create stock that is to be bought
        auto stockPtr = std::make_shared<Stock>(-1, stock, quantity); // Reconsider how this is done
        user->placeOrder(stockPtr, OrderType::BUY, quantity, price);
    }, user);
}

void handleSell(const Variant user, const std::string& stock, int quantity, double price) {
    std::visit([&](auto&& user) {
        // Check if excange is nullptr
        if (user->exchange == nullptr) {
            std::cerr << "User has not joined an exchange\n";
            return;
        }
        // Find the stock that is to be sold. This throws if the user does not own the stock
        // Im sorry søren, its really not the best way
        auto stockPtr = user->getStock(stock);
        
        // Check if the user has enough stocks to sell
        if (stockPtr->getNumberOfStocks() < quantity) {
            std::cerr << "User does not own enough stocks\n";
            return;
        }

        user->placeOrder(stockPtr, OrderType::SELL, quantity, price);
    }, user);
}

void handleOrder(const Variant user, const std::string& stock, int quantity, double price, std::string orderType) {
    if (orderType == "buy") {
        handleBuy(user, stock, quantity, price);
    } else if (orderType == "sell") {
        handleSell(user, stock, quantity, price);
    } else {
        throw std::invalid_argument("Unknown order type: " + orderType);
    }
}

void handleAvailable(const Variant user) {
    // Access exchange through the user and show available stocks
    std::visit([](auto&& user) {
        // Check if excange is nullptr
        if (user->exchange == nullptr) {
            std::cerr << "User has not joined an exchange\n";
            return;
        }
        user->exchange->displayAvailableStocks();
    }, user);
}

void handleInfo(Variant user) {
    // Display information about the user
    std::visit([](auto&& user) {
        user->displayPortfolio();
    }, user);
}

void handleCreate(Variant user, const std::string symbol, const int num) {
    if(!std::holds_alternative<std::shared_ptr<Company>>(user)) {
        std::cerr << "You are not a company, you cannot create stocks\n";
        return;
    }
    static int stockID = 0; // Ensures we have unique IDs
    auto& company = std::get<std::shared_ptr<Company>>(user);
    company->createStock(stockID, symbol, num);
    stockID++;
}

// Function to display the help message
void displayHelp() {
    std::cout << "Available commands:\n"
              << "  info                                    Display information about the user\n"
              << "  buy <stock> <quantity> <total price>    Buy stocks\n"
              << "  sell <stock> <quantity> <total price>   Sell stocks\n"
              << "  available                               Display available stocks\n"
              << "  create <name> <quantity>                Create a stock (only available if you are a company)\n" // CHANGE TO NOT BE ABLE TO SEE
              << "  help                                    Display this help message\n"
              << "  exit                                    Exit the program\n";
}