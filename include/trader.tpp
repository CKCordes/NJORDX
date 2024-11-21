#ifndef TRADER_H
#define TRADER_H


#include <vector>
#include <string>
#include "stock.hpp"
#include "order.hpp"
#include "njordx.hpp"
#include "stockOrderBook.tpp"

template <typename Derived>
class Trader {
    private:
        int traderID;
        double balance;
        OrderBook<std::string, Stock&> ownedStocks;
        Njordx* exchange;

        //int getOrderID() const;

    public:

        Trader(int, double, Njordx*);
        ~Trader() = default;

        void printTrader() const;
        void displayPortfolio() const;

        double getBalance() const;
        void setBalance(double amount);

        void addStock(const Stock);
        void removeStock(const Stock&);

        bool placeBuyOrder(const Stock&, int, double);
        bool placeSellOrder(int, OrderType, int, std::string, int, double);

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


#endif // TRADER_H