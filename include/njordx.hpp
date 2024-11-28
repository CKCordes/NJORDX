#ifndef NJORDX_H
#define NJORDX_H

#include <vector>
#include <string>

#include "stockOrderBook.tpp"
#include "order.hpp"
#include "ITrader.hpp"

class Njordx {
private:   
    OrderBook<int, Order> buyOrders; /* Key: OrderID, Value: Order */
    OrderBook<int, Order> sellOrders; /* Key: OrderID, Value: Order */
    OrderBook<std::string, int> validStocks; /* Key: Stocksymbol, Value: StockID */
    std::vector<ITrader*> traders;
public:
    // Constructor, no need for rule of 3
    Njordx();

    // Order management methods
    bool addBuyOrder(Order* order) noexcept; // Not const to accomodate Strong guarentee on stockorderbook
    bool addSellOrder(Order* order) noexcept; // Not const to accomodate Strong guarentee on stockorderbook
    void addTrader(ITrader* trader) noexcept;

    // Display methods
    void matchOrders();
    void displayOrderBook(const OrderType type) const;
};

#endif // NJORDX_H
