#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>
#include <memory>

#include "stock.hpp"

enum class OrderType { BUY, SELL };

class Order {
private:
    int orderID;
    OrderType type;
    int traderID;   
    std::shared_ptr<Stock> stock;
    int quantity;
    double price;
    bool isFilled;

public:
    // Constructor
    Order(int id, OrderType type, int traderID, std::string stockSymbol, std::shared_ptr<Stock> stock, int quantity, double price);

    // Getters and setters
    int getOrderID() const;
    OrderType getOrderType() const;
    int getTraderID() const;
    int getStockID() const;
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
