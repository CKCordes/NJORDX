#ifndef NJORDX_H
#define NJORDX_H

#include <vector>

#include "stockOrderBook.tpp"
#include "order.hpp"

class Njordx {
private:   
    OrderBook<int, Order> buyOrders;
    OrderBook<int, Order> sellOrders;

public:
    // Constructor, no need for rule of 3
    Njordx();

    // Order management methods
    void addOrder(const OrderType type, const Order* order);
    Order matchOrders();

    // Display methods
    void displayOrderBook(const OrderType type) const;
};

#endif // NJORDX_H
