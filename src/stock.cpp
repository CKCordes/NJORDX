#include <iostream>

#include "stock.hpp"

Stock::Stock(int id, const std::string& symbol, int numberOfStocks) 
    : stockID(id), symbol(symbol), numberOfStocks(numberOfStocks) {}

int Stock::getStockID() const {
    return stockID;
}

std::string Stock::getSymbol() const {
    return symbol;
}

int Stock::getNumberOfStocks() const {
    return numberOfStocks;
}

void Stock::addStocks(int amount) noexcept {
    int newAmount = numberOfStocks + amount;
    numberOfStocks = std::move(newAmount);
}

void Stock::removeStocks(int amount) {
    int newAmount = numberOfStocks - amount;
    if (newAmount < 0) {
        std::cerr << "Cannot remove more stocks than owned" << std::endl;
        return; 
    }
    numberOfStocks = newAmount;
}

void Stock::displayInfo() const {
    std::cout << "Stock ID: " << stockID << std::endl;
    std::cout << "Symbol: " << symbol << std::endl;
    std::cout << "Number of stocks: " << numberOfStocks << std::endl;
}

// Operator overloading
bool Stock::operator==(const Stock& other) const {
    return stockID == other.stockID && symbol == other.symbol;
}