#ifndef NJORDX_H
#define NJORDX_H

#include <vector>
#include <string>

#include "stockOrderBook.tpp"
#include "order.hpp"

class Njordx {
private:   
    OrderBook<int, Order> buyOrders;
    OrderBook<int, Order> sellOrders;
    OrderBook<std::string, int> validStocks;

public:
    // Constructor, no need for rule of 3
    Njordx();

    // Order management methods
    bool addOrder(const OrderType type, Order* order);
    Order matchOrders();

    // Display methods
    void displayOrderBook(const OrderType type) const;

    // 
};

#endif // NJORDX_H
