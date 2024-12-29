#ifndef NJORDX_H
#define NJORDX_H

#include <vector>
#include <string>

#include "stockOrderBook.tpp"
#include "order.hpp"
#include "ITrader.hpp"

class Njordx {
private:   
    OrderBook<int, std::shared_ptr<Order>> buyOrders; /* Key: OrderID, Value: Order */
    OrderBook<int, std::shared_ptr<Order>> sellOrders; /* Key: OrderID, Value: Order */
    OrderBook<std::string, int> validStocks; /* Key: Stocksymbol, Value: StockID */
    std::vector<ITrader*> traders;
public:
    // Constructor, no need for rule of 3
    Njordx();

    // Order management methods
    void addOrder(std::shared_ptr<Order> order) noexcept;
    void addTrader(ITrader* trader) noexcept;

    // Display methods
    void matchOrders();
    void displayOrderBook(const OrderType type); // missing const
    void displayAvailableStocks(); // missing const

    void processOrders(const std::function<void(std::shared_ptr<Order>)>& callback);
    void displayAllOrders();
};

#endif // NJORDX_H
