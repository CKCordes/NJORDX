#include "order.hpp"


// Constructor
Order::Order(int id, OrderType type, int traderID, int stockID, int quantity, double price)
    : orderID(id), type(type), traderID(traderID), stockID(stockID), quantity(quantity), price(price) {}

// Getters
int Order::getOrderID() const {
    return orderID;
}

OrderType Order::getOrderType() const {
    return type;
}

int Order::getTraderID() const {
    return traderID;
}

std::string Order::getStockSymbol() const {
    return stockSymbol;
}

int Order::getQuantity() const {
    return quantity;
}

double Order::getPrice() const {
    return price;
}

void Order::setIsFilled(bool status) {
    isFilled = status;
}

void Order::displayOrderDetails() const {
    std::cout << "Order ID: " << orderID << std::endl;
    std::cout << "Order Type: " << (type == OrderType::BUY ? "BUY" : "SELL") << std::endl;
    std::cout << "Trader ID: " << traderID << std::endl;
    std::cout << "Stock ID: " << stockSymbol << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "Is Filled: " << (isFilled ? "Yes" : "No") << std::endl;
}