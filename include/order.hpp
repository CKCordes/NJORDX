#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>
#include <memory>

#include "stock.hpp"
#include "config.hpp"

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

    int constructOrderID();

public:
    // Constructor
    Order(OrderType type, int traderID, std::shared_ptr<Stock> stock, int quantity, double price);

    // Getters and setters
    int getOrderID() const;
    OrderType getOrderType() const;
    std::string getStockSymbol() const;
    int getTraderID() const;
    int getStockID() const;
    int getQuantity() const;
    double getPrice() const;
    bool getIsFilled() const;
    void setIsFilled(bool status);
    std::shared_ptr<Stock> getStock() const;

    // Display order information
    void displayOrderDetails() const;

    // Overloaded equality operator
    bool operator==(const Order& other) const;
};

#endif // ORDER_H
