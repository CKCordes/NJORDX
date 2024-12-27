#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <variant>

#include "njordx.hpp"
#include "company.tpp"
#include "person.tpp"

// Function prototypes
void handleBuy(const std::variant<Person, Company> user, const std::string& stock);
void handleSell(const std::variant<Person, Company> user, const std::string& stock);
void handleAvailable(const std::variant<Person, Company> user);
void handleInfo(std::variant<Person, Company> user);
void handleCreate(const std::variant<Person, Company> user, const std::string symbol, const int num);
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
    std::variant<Person, Company> user;

    if (user_tp == "person") {
        user = Person(1, balance, exchange, name, reg_number);
        // std::cout << "Creating a new person with name: " << name << " and reg. number: " << reg_number << "\n";
    } else if (user_tp == "company") {
        // std::cout << "Creating a new company with name: " << name << " and reg. number: " << reg_number << "\n";
        user = Company(1, balance, exchange, name, reg_number);
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

            if (command == "buy") {
                std::string stock;
                iss >> stock;
                if (stock.empty()) {
                    throw std::invalid_argument("Usage: buy <stock>");
                }
                handleBuy(user, stock);
            } else if (command == "sell") {
                std::string stock;
                iss >> stock;
                if (stock.empty()) {
                    throw std::invalid_argument("Usage: sell <stock>");
                }
                handleSell(user, stock);
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
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}

void handleBuy(const std::variant<Person, Company> user, const std::string& stock) {
    std::cout << "Unimplemented\n";
}

void handleSell(const std::variant<Person, Company> user, const std::string& stock) {
    std::cout << "Unimplemented\n";
}

void handleAvailable(const std::variant<Person, Company> user) {
    // Access exchange through the user and show available stocks
    std::visit([](auto&& user) {
        // Check if excange is nullptr
        if (user.exchange == nullptr) {
            std::cerr << "User has not joined an exchange\n";
            return;
        }
        user.exchange->displayAvailableStocks();
    }, user);
}

void handleInfo(std::variant<Person, Company> user) {
    // Display information about the user
    std::visit([](auto&& user) {
        user.displayPortfolio();
    }, user);
}

void handleCreate(std::variant<Person, Company> user, const std::string symbol, const int num) {
    if(!std::holds_alternative<Company>(user)) {
        std::cerr << "You are not a company, you cannot create stocks\n";
        return;
    }
    static int stockID = 0; // Ensures we have unique IDs
    auto& company = std::get<Company>(user);
    company.createStock(stockID, symbol, num);
    if (company.ownedStocks.contains(symbol)) {
        std::cout << "Stock created successfully\n";
    }
    stockID++;
}

// Function to display the help message
void displayHelp() {
    std::cout << "Available commands:\n"
              << "  info                        Display information about the user\n"
              << "  buy <stock>                 Buy stocks\n"
              << "  sell <stock>                Sell stocks\n"
              << "  available                   Display available stocks\n"
              << "  create <name> <quantity>    Create a stock (only available if you are a company)\n" // CHANGE TO NOT BE ABLE TO SEE
              << "  help                        Display this help message\n"
              << "  exit                        Exit the program\n";
}