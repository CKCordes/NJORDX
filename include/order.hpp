#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>
#include <memory>

#include "trader.hpp"

enum class OrderType { BUY, SELL };

class Order {
private:
    int orderID;
    OrderType type;
    
    std::shared_ptr<Trader> trader;
    
    std::string stockSymbol;
    int stockID;
    int quantity;
    double price;
    bool isFilled;

public:
    // Constructor
    Order(int id, OrderType type, int traderID, std::string stockSymbol, int quantity, double price);

    // Getters and setters
    int getOrderID() const;
    OrderType getOrderType() const;
    int getTraderID() const;
    std::string getStockSymbol() const;
    int getStockID() const;
    void setStockID(int id);
    int getQuantity() const;
    double getPrice() const;
    bool getIsFilled() const;
    void setIsFilled(bool status);

    // Display order information
    void displayOrderDetails() const;

    // Overloaded equality operator
    bool operator==(const Order& other) const;
};

#endif // ORDER_H
