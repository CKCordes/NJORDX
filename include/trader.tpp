#ifndef TRADER_H
#define TRADER_H


#include <vector>
#include <string>
#include "stock.hpp"
#include "order.hpp"
#include "njordx.hpp"
#include "stockOrderBook.tpp"
#include "ITrader.hpp"

template <typename Derived>
class Trader : ITrader {
    private:
        int traderID;
        double balance;
        OrderBook<std::string, Stock&> ownedStocks;
        Njordx* exchange;

        //int getOrderID() const;

    public:

        Trader(int, double, Njordx*);
        ~Trader() = default;

        void printTrader() const override;
        void displayPortfolio() const override;

        double getBalance() const override;
        void setBalance(double amount) override;

        void addStock(const Stock) override;
        void removeStock(const Stock&) override;

        bool placeBuyOrder(const Stock&, int, double) override;
        bool placeSellOrder(int, OrderType, int, std::string, int, double) override;

        void handleOrder(const Order&) override;

};

template <typename Derived>
Trader<Derived>::Trader(int id, double initialBalance, Njordx* exchange) 
    : traderID(id), balance(initialBalance), exchange(exchange) {}


template <typename Derived>
void Trader<Derived>::printTrader() const {
    static_cast<const Derived*>(this)->printTrader();}

template <typename Derived>
void Trader<Derived>::displayPortfolio() const {
    static_cast<const Derived*>(this)->displayPortfolio();
}

template <typename Derived>
double Trader<Derived>::getBalance() const {
    return balance;
}

template <typename Derived>
void Trader<Derived>::setBalance(double amount) {
    balance = amount;
}

template <typename Derived>
void Trader<Derived>::addStock(const Stock stock) {
    ownedStocks.insert(stock.getSymbol(), stock);
}

template <typename Derived>
void Trader<Derived>::removeStock(const Stock& stock) {
    ownedStocks.erase(stock.getSymbol());
}

template <typename Derived>
bool Trader<Derived>::placeBuyOrder(const Stock& stock, int quantity, double price) {
    Order newOrder = Order(1, OrderType::BUY, traderID, stock.getSymbol(), quantity, price);

    try {
        exchange->addBuyOrder(&newOrder);
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

template <typename Derived>
bool Trader<Derived>::placeSellOrder(int id, OrderType type, int traderID, std::string stockSymbol, int quantity, double price) {
    Order newOrder = Order(id, type, traderID, stockSymbol, quantity, price);

    try {
        exchange->addSellOrder(&newOrder);
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

template <typename Derived>
void Trader<Derived>::handleOrder(const Order& order) {
    raise std::logic_error("Not implemented");
}


#endif // TRADER_H