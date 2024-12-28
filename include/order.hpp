#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <iostream>
#include <memory>

#include "stock.hpp"
#include "config.hpp"

enum class OrderType { BUY, SELL, OPTION, FUTURE, SPOT };

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
    auto getTraderID() const -> decltype(traderID);
    int getStockID() const;
    int getQuantity() const;
    auto getPrice() const -> decltype(price);
    bool getIsFilled() const;
    void setIsFilled(bool status);
    void setPrice(double price);
    auto getStock() const -> decltype(stock);

    // Display order information
    void displayOrderDetails() const;

    // Overloaded equality operator
    bool operator==(const Order& other) const;
};

#endif // ORDER_H
