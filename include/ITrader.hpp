#ifndef ITRADER_HPP
#define ITRADER_HPP

#include <string>
#include "stock.hpp"
#include "order.hpp"

class ITrader {
public: 
    virtual ~ITrader() = default;

    virtual void printTrader() const = 0;
    virtual void displayPortfolio() const = 0;

    virtual int getTraderID() const = 0;
    virtual double getBalance() const = 0;
    virtual void setBalance(double amount) = 0;

    virtual void addStock(const Stock&) = 0;
    virtual void removeStock(const Stock&) = 0;

    virtual bool placeBuyOrder(const Stock&, int, double) = 0;
    virtual bool placeSellOrder(int, OrderType, int, std::string, int, double) = 0;

    virtual void handleOrder(const Order&) = 0;
};

#endif // ITRADER_HPP