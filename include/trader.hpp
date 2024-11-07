#ifndef TRADER_H
#define TRADER_H

#include <vector>
#include <string>
#include "stock.hpp"
#include "order.hpp"
#include "njordx.hpp"

class Trader {
protected:
    int traderID;
    double balance;
    std::vector<Stock> ownedStocks;
    Njordx* exchange;

    int getOrderID() const;

public:
    // Pure virtual destructor to make Trader an abstract class
    virtual ~Trader() = 0;

    // Pure virtual method for displaying portfolio, making Trader abstract
    virtual void displayPortfolio() const = 0;

    // Getters and setters for balance
    double getBalance() const;
    void setBalance(double amount);

    // Stock management methods
    void addStock(const Stock& stock);
    void removeStock(const Stock& stock);

    // Order methods
    virtual Order placeBuyOrder(const Stock& stock, int quantity, double price);
    virtual Order placeSellOrder(const Stock& stock, int quantity, double price);

    // Abstract method for creating a stock and adding it to the exchange
    virtual Stock createStock(int stockID, const std::string& symbol, double initialPrice) = 0;
};

// Inline definition of pure virtual destructor
inline Trader::~Trader() {}
#endif // TRADER_H
