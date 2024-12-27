#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <variant>

#include "njordx.hpp"
#include "company.tpp"
#include "person.tpp"
#include "stock.hpp"

// Function prototypes
void handleBuy(const std::string& stockName, const int& quantity, const double& price, Njordx* exchange, std::variant<Person, Company>& user);
void handleSell(const std::string& stockName, const int& quantity, const double& price, Njordx* exchange, std::variant<Person, Company>& user);
void handleAvailable() {
    throw std::logic_error("Unimplemented");
}
void handleInfo(const std::variant<Person, Company>& user);
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
    
    std::string user_tp = argv[1];
    std::string name = argv[2];
    std::string reg_number = argv[3];
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
                int quantity;
                double price;
                iss >> stock;
                iss >> quantity;
                iss >> price;
                if (stock.empty()) { // TODO: Skal tilføje manglede argumenter
                    throw std::invalid_argument("Usage: buy <stock> <quantity> <price>");
                }
                handleBuy(stock, quantity, price, exchange, user);
            } else if (command == "sell") {
                 std::string stock;
                int quantity;
                double price;
                iss >> stock;
                iss >> quantity;
                iss >> price;
                if (stock.empty()) { // TODO: Skal tilføje manglede argumenter
                    throw std::invalid_argument("Usage: sell <stock> <quantity> <price>");
                }
                handleSell(stock, quantity, price, exchange, user);
            } else if (command == "info") {
                handleInfo(user);
            } else if (command == "available") {
                handleAvailable();
            } else if (command == "help") {
                displayHelp();
            } else {
                throw std::invalid_argument("Unknown command: " + command + ". Type 'help' for a list of commands.");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}

// Function to handle the "add" command
void handleAdd(const std::string& num1, const std::string& num2) {
    try {
        int a = std::stoi(num1);
        int b = std::stoi(num2);
        std::cout << "Result: " << a + b << "\n";
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("Invalid input: '" + num1 + "' or '" + num2 + "' is not a number.");
    } catch (const std::out_of_range&) {
        throw std::out_of_range("Number out of range. Please use smaller values.");
    }
}

// Function to handle the "greet" command
void handleBuy(const std::string& stockName, const int& quantity, const double& price, Njordx* exchange, std::variant<Person, Company>& user) {
    int stockID = exchange->getValidStockID(stockName);
    Stock stock = Stock(stockID, stockName, quantity); // ? Hvad skal numberOfStocks være her? Sat til quantity for nu

    if (std::holds_alternative<Person>(user)) {
        std::get<Person>(user).placeOrder(stock, OrderType::BUY, quantity, price);
    } else {
        std::get<Company>(user).placeOrder(stock, OrderType::BUY, quantity, price);
    }

}  

void handleSell(const std::string& stockName, const int& quantity, const double& price, Njordx* exchange, std::variant<Person, Company>& user) {
    // int stockID = exchange->getValidStockID(stockName);
    // TODO: giv et rigtigt stockID, som ikke er 111
    Stock stock = Stock(111, stockName, quantity); // ? Hvad skal numberOfStocks være her? Sat til quantity for nu

    if (std::holds_alternative<Person>(user)) {
        std::get<Person>(user).placeOrder(stock, OrderType::SELL, quantity, price);
    } else {
        std::get<Company>(user).placeOrder(stock, OrderType::SELL, quantity, price);
    }
}

void handleInfo(const std::variant<Person, Company>& user) {
    if (std::holds_alternative<Person>(user)) {
        std::get<Person>(user).displayPortfolio();
    } else {
        std::get<Company>(user).displayPortfolio();
    }
}

// Function to display the help message
void displayHelp() {
    std::cout << "Available commands:\n"
              << "  info                  Display information about the user\n"
              << "  buy                   Buy stocks\n"
              << "  sell                  Sell stocks\n"
              << "  available             Display available stocks\n"
              << "  help                  Display this help message\n"
              << "  exit                  Exit the program\n";
}
