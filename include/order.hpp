#ifndef ORDER_H
#define ORDER_H

#include <string>

enum class OrderType { BUY, SELL };

class Order {
private:
    int orderID;
    OrderType type;
    int traderID;
    int stockID;
    int quantity;
    double price;
    bool isFilled;

public:
    // Constructor
    Order(int id, OrderType type, int traderID, std::string symbol, int quantity, double price);

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
};

#endif // ORDER_H
