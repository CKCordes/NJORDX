#ifndef TRADER_H
#define TRADER_H

#include <vector>
#include <string>
#include "stock.hpp"
#include "order.hpp"

class Trader {
private:
    int traderID;
    std::string name;
    std::vector<Stock> ownedStocks;
    double balance;

public:
    // Constructor
    Trader(int id, const std::string& name, double initialBalance);

    // Getters and setters
    double getBalance() const;
    void setBalance(double amount);

    // Stock management methods
    void addStock(const Stock& stock);
    void removeStock(const Stock& stock);

    // Order methods
    Order placeBuyOrder(const Stock& stock, int quantity, double price);
    Order placeSellOrder(const Stock& stock, int quantity, double price);

    // Display information
    void displayPortfolio() const;
};

#endif // TRADER_H
