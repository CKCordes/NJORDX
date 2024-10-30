#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <vector>
#include "order.hpp"
#include "stock.hpp"

class Exchange {
private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
    std::vector<Stock> availableStocks;

public:
    // Constructor
    Exchange();

    // Order management methods
    void addBuyOrder(const Order& order);
    void addSellOrder(const Order& order);
    void matchOrders();

    // Stock management
    void addStock(const Stock& stock);
    Stock* findStock(int stockID);
    void updateStockPrice(int stockID, double newPrice);

    // Display methods
    void displayOrderBook() const;
    void displayAvailableStocks() const;
};

#endif // EXCHANGE_H
