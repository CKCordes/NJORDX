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
    bool addBuyOrder(Order* order) const noexcept;
    bool addSellOrder(Order* order) const noexcept;
    Order matchOrders();

    // Display methods
    void displayOrderBook(const OrderType type) const;

    // 
};

#endif // NJORDX_H
