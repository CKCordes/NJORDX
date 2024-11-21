#include "order.hpp"


// Constructor
Order::Order(int id, OrderType type, int traderID, std::string stockSymbol, std::shared_ptr<Stock> stock, int quantity, double price)
    : orderID(id), type(type), traderID(traderID), stockSymbol(stockSymbol), stock(stock), quantity(quantity), price(price), isFilled(false) {}

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

int Order::getStockID() const {
    return stock.get()->getStockID();
}

int Order::getQuantity() const {
    return quantity;
}

double Order::getPrice() const {
    return price;
}

bool Order::getIsFilled() const {
    return isFilled;
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

bool Order::operator==(const Order& other) const {
    return orderID == other.orderID;
}