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

int Order::getStockID() const {
    return stockID;
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