#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <variant>

#include "njordx.hpp"
#include "company.tpp"
#include "person.tpp"

using Variant = std::variant<std::shared_ptr<Person>, std::shared_ptr<Company>>;

// todo: Function prototypes (er det stadig prototyper?)
void handleBuy(const Variant user, const std::string& stock, int quantity, double price);
void handleSell(const Variant user, const std::string& stock, int quatity, double price);

void handleAvailable(const Variant user);
void handleInfo(Variant user);
void handleCreate(const Variant user, const std::string symbol, const int num);
void displayHelp();

// Functions for simulating activity
void handleBuyBot(std::shared_ptr<Company> bot_user, std::string stockToBuy);
void handleSellBot(std::shared_ptr<Company> bot_user);
void showOrders(Njordx* exchange);
void handleShowOrderBook(Njordx* exchange, const OrderType type);

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

    // User is a variant that can be either a person or a company
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

    // Creating the bot user
    std::shared_ptr<Company> bot_user = std::make_shared<Company>(2, 100000, exchange, "Søren", "1234567890");

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
                    throw std::invalid_argument("Usage: buy <stock> <quantity> <price>");
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
                if (price < 0) {
                    throw std::invalid_argument("Error: Price cannot be negative.");
                }
                if (quantity <= 0) {
                    throw std::invalid_argument("Error: Quantity cannot be negative.");
                }
                (command == "buy" ? handleBuy : handleSell)(user, stock, quantity, price);
            
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
            } else if (command == "show_orders") {
                showOrders(exchange);
            } else if (command == "show_order_book") {
                std::string orderType;
                iss >> orderType;
                if (orderType.empty()) {
                    throw std::invalid_argument("Usage: show_order_book <buy/sell>");
                }
                if (orderType == "buy") {
                    handleShowOrderBook(exchange, OrderType::BUY);
                } else if (orderType == "sell") {
                    handleShowOrderBook(exchange, OrderType::SELL);
                } else {
                    throw std::invalid_argument("Usage: show_order_book <buy/sell>");
                }
            }
            
            else if (command == "buy_bot") {
                std::string stockToBuy;
                iss >> stockToBuy;
                if (stockToBuy.empty()) {
                    throw std::invalid_argument("Usage: buy_bot <stock-to-buy>");
                }
                handleBuyBot(bot_user, stockToBuy);
            } else if (command == "sell_bot") {
                handleSellBot(bot_user);
            }
            else {
                throw std::invalid_argument("Unknown command: " + command + ". Type 'help' for a list of commands.");
            }
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}

void handleBuy(const Variant user, const std::string& stock, int quantity, double price) {
     std::visit([&](auto&& user) {
        // Check if excange is nullptr
        if (user->exchange == nullptr) {
            std::cerr << "User has not joined an exchange\n";
            return;
        }
        // Create stock that is to be bought
        auto stockPtr = std::make_shared<Stock>(-1, stock, quantity); // todo: Reconsider how this is done
        user->placeOrder(stockPtr, OrderType::BUY, quantity, price);
    }, user);
}

void handleSell(const Variant user, const std::string& stock, int quantity, double price) {
    std::visit([&](auto&& user) {
        // Check if exchange is nullptr
        if (user->exchange == nullptr) {
            std::cerr << "User has not joined an exchange\n";
            return;
        }
        // Check if user owns the stock
        auto stockOpt = user->getStock(stock);
        if (!stockOpt.has_value()) {
            std::cerr << "User does not own the stock\n";
            return;
        }
        auto stock = stockOpt.value();
        // Check if the user has enough stocks to sell

        user->placeOrder(stock, OrderType::SELL, quantity, price);
    }, user);
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


void handleBuyBot(std::shared_ptr<Company> bot_user, const std::string stockToBuy) {
    handleBuy(bot_user, stockToBuy, 1, 100);
    std::cout << "Bot is buying 1 " << stockToBuy << " for 100\n";
}

void handleSellBot(std::shared_ptr<Company> bot_user) {
    std::vector<std::string> stockNames = {"AAPL", "GOOGL", "MSFT", "AMZN", "TSLA"};
    std::string randomStock = stockNames[rand() % stockNames.size()];
    int price = rand() % 100 + 1;
    handleCreate(bot_user, randomStock, 1);
    handleSell(bot_user, randomStock, 1, price);
    std::cout << "Bot is selling 1 " << randomStock << " for " << price << "\n";   
}

void showOrders(Njordx* exchange) {
    // Show all orders
    std::cout << "Showing all orders\n";
    exchange->displayAllOrders();
}

void handleShowOrderBook(Njordx* exchange, const OrderType type) {
    exchange->displayOrderBook(type);
}

// Function to display the help message
void displayHelp() {
    std::cout << "Available commands:\n"
              << "  info                                    Display information about the user\n"
              << "  buy <stock> <quantity> <total price>    Buy stocks\n"
              << "  sell <stock> <quantity> <total price>   Sell stocks\n"
              << "  available                               Display available stocks\n"
              << "  create <name> <quantity>                Create a stock (only available if you are a company)\n" // CHANGE TO NOT BE ABLE TO SEE IF PERSON
              << "  show_orders                             Show all orders\n"
              << "  show_order_book <buy/sell>              Show buy or sell orders\n"
              << "  buy_bot <stock-to-buy>                  Simulate a user posting buy order (price=100) on a stock of your choice\n"
              << "  sell_bot                                Simulate a user posting random sell orders you can match\n"
              << "  help                                    Display this help message\n"
              << "  exit                                    Exit the program\n";
}