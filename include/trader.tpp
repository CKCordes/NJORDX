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
    protected:
        int traderID;
        double balance;
        OrderBook<std::string, Stock> ownedStocks;
        Njordx* exchange;

        //int getOrderID() const;
        void buyStock(std::shared_ptr<Stock> stock, double total) override;
        void sellStock(std::shared_ptr<Stock> stock, double total) override;

    public:

        Trader(int, double, Njordx*);
        ~Trader() = default;

        void printTrader() const override;
        void displayPortfolio() const override;

        int getTraderID() const override { return traderID; }
        double getBalance() const override;
        void setBalance(double amount) override;

        void addStock(const Stock) override;
        void removeStock(const Stock&) override;
        Stock getStock(const std::string& symbol) const;

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
    Order newOrder = Order(1, OrderType::BUY, traderID, std::make_shared<Stock>(stock), quantity, price);

    try {
        exchange->addBuyOrder(&newOrder);
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

template <typename Derived>
Stock Trader<Derived>::getStock(const std::string& symbol) const {
    return ownedStocks.get(symbol);
}

template <typename Derived>
bool Trader<Derived>::placeSellOrder(int id, OrderType type, int traderID, std::string stockSymbol, int quantity, double price) {
    Stock stock = getStock(stockSymbol);
    Order newOrder = Order(id, type, traderID, std::make_shared<Stock>(stock), quantity, price);

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

    double price = order.getPrice();
    int quantity = order.getQuantity();
    double total = price * quantity;
    std::shared_ptr<Stock> stock = order.getStock();

    OrderType type = order.getOrderType();
    switch(type) {
        case OrderType::BUY:
            buyStock(stock, total);
            break;
        case OrderType::SELL:
            sellStock(stock, total);
            break;
        default:
            std::cerr << "Invalid order type" << std::endl;
    }  
}

template <typename Derived>
void Trader<Derived>::buyStock(std::shared_ptr<Stock> stock, double total) {
    balance -= total;
    addStock(*stock);
}

template <typename Derived>
void Trader<Derived>::sellStock(std::shared_ptr<Stock> stock, double total) {
    balance += total;
    removeStock(*stock);
}





#endif // TRADER_H