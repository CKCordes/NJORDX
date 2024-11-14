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

        int getOrderID() const;
        void printTrader() const;

    public:

        Trader(int, double, Njordx*);
        ~Trader();

        void displayPortfolio() const;
        double getBalance() const;
        void setBalance(double amount);

        void addStock(const Stock);
        void removeStock(const Stock&);

        Order placeBuyOrder(const Stock&, int, double);
        Order placeSellOrder(const Stock&, int, double);


};

template <typename Derived>
Trader<Derived>::Trader(int id, double initialBalance, Njordx* exchange) 
    : traderID(id), balance(initialBalance), exchange(exchange) {}

template <typename Derived>
Trader<Derived>::printTrader() const {
    // std::cout << "Trader ID: " << traderID << "\nBalance: " << balance << "\nOwned Stocks: \n";
    static_cast<const Derived*>(this)->printTrader();
}

template <typename Derived>
void Trader<Derived>::displayPortfolio() const {
    static_cast<const Derived*>(this)->printTrader();

   
    //for (auto stock : ownedStocks) {
    //    stock.displayInfo();
    //}
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
Order Trader<Derived>::placeBuyOrder(const Stock& stock, int quantity, double price) {
    throw std::logic_error("Not implemented yet");
}

template <typename Derived>
Order Trader<Derived>::placeSellOrder(const Stock& stock, int quantity, double price) {
    throw std::logic_error("Not implemented yet");
}

class Company : public Trader<Company>{

private:
    printTrader() const {
        std::cout << "Trader ID: " << traderID << "\nBalance: " << balance << "\nOwned Stocks: \n";
        for (auto stock : ownedStocks) {
            stock.displayInfo();
        }
    }

}

#endif // TRADER_H