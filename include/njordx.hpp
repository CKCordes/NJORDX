#ifndef NJORDX_H
#define NJORDX_H

#include <vector>

#include "stockOrderBook.hpp"
#include "order.hpp"
#include "stock.hpp"

class Njordx {
private:
    //OrderBook<int, Order> buyOrders;
    //OrderBook<int, Order> sellOrders;
    
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;

public:
    // Constructor
    Njordx();

    // Order management methods
    void addBuyOrder(const Order* order);
    void addSellOrder(const Order* order);
    void matchOrders();

    // Display methods
    void displayOrderBook() const;
};

#endif // NJORDX_H
