#include <iostream>

#include "stock.hpp"

Stock::Stock(int id, const std::string& symbol, double initialPrice) 
    : stockID(id), symbol(symbol), price(initialPrice) {}

int Stock::getStockID() const {
    return stockID;
}

std::string Stock::getSymbol() const {
    return symbol;
}

double Stock::getPrice() const {
    return price;
}

void Stock::setPrice(double newPrice) {
    price = newPrice;
}

void Stock::displayInfo() const {
    std::cout << "Stock ID: " << stockID << std::endl;
    std::cout << "Symbol: " << symbol << std::endl;
    std::cout << "Price: " << price << std::endl;
}