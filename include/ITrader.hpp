#ifndef ITRADER_HPP
#define ITRADER_HPP

#include <string>
#include "stock.hpp"
#include "order.hpp"

class Njordx;

class ITrader {
public: 
    virtual ~ITrader() = default;

    virtual void buyStock(std::shared_ptr<Stock>, double, int) = 0;
    virtual void sellStock(std::shared_ptr<Stock>, double, int) = 0;

    virtual void printTrader() const = 0;
    virtual void displayPortfolio() = 0;

    virtual int getTraderID() const = 0;
    virtual double getBalance() const = 0;
    virtual void setBalance(double amount) = 0;

    virtual void addStock(std::shared_ptr<Stock>) = 0;
    virtual void removeStock(std::shared_ptr<Stock>) = 0;
    virtual bool ownsStock(const std::string symbol) = 0;

    virtual void placeOrder(const std::shared_ptr<Stock>, const OrderType, int, double) = 0;

    virtual void handleOrder(const std::shared_ptr<Order>, int) = 0;
    virtual void joinExchange(Njordx* exchange) = 0;
};

#endif // ITRADER_HPP