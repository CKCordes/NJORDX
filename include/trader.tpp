#ifndef TRADER_H
#define TRADER_H


#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <memory>
#include "stock.hpp"
#include "order.hpp"
#include "njordx.hpp"
#include "stockOrderBook.tpp"
#include "ITrader.hpp"

class Company; // Forward declaration
class Person; // Forward declaration

template <typename Derived>
class Trader : public ITrader {
    protected:
        int traderID;
        double balance;

        void buyStock(std::shared_ptr<Stock> stock, double total, int bought_quantity) override;
        void sellStock(std::shared_ptr<Stock> stock, double total, int bought_quantity) override; 
        void addStock(std::shared_ptr<Stock> stock);
        void removeStock(std::shared_ptr<Stock> stock);

        OrderBook<std::string, std::shared_ptr<Stock>> ownedStocks; // CHANGE TO PROTECTED AGAIN!
        // Add currency to balance
    public:
        Njordx* exchange;

        Trader(int, double, Njordx*);
        Trader(int, double);
        ~Trader() = default;

        void printTrader() const override;
        void displayPortfolio() override;

        int getTraderID() const override { return traderID; };
        double getBalance() const override;
        void setBalance(double amount) override;
        bool ownsStock(const std::string symbol);

        // Enable if the derived class is a company
        template <typename T = Derived>
        typename std::enable_if<std::is_same<T, Company>::value, void>::type
        createStock(int stockID, const std::string& symbol, int numberOfStocks) {
            auto newStock = std::make_shared<Stock>(stockID, symbol, numberOfStocks);
            ownedStocks.insert(symbol, newStock);
        }

        std::shared_ptr<Stock> getStock(const std::string& symbol) const;

        void placeOrder(const std::shared_ptr<Stock>, const OrderType, int, double) override;

        void handleOrder(const std::shared_ptr<Order>, int) override;

        void joinExchange(Njordx* exchange) override { this->exchange = exchange; exchange->addTrader(this); };

};

// Delegating constructors
template <typename Derived>
Trader<Derived>::Trader(int id, double initialBalance) 
    : Trader<Derived>(id, initialBalance, nullptr) {}  

template <typename Derived>
Trader<Derived>::Trader(int id, double initialBalance, Njordx* exchange) 
    : traderID(id), balance(initialBalance), exchange(exchange) {if (exchange != nullptr) exchange->addTrader(this);}



template <typename Derived>
void Trader<Derived>::printTrader() const {
    static_cast<const Derived*>(this)->printTrader();}

template <typename Derived>
void Trader<Derived>::displayPortfolio() {
    static_cast<Derived*>(this)->displayPortfolio();
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
void Trader<Derived>::addStock(std::shared_ptr<Stock> stock) {
    ownedStocks.insert(stock->getSymbol(), stock);
}

template <typename Derived>
void Trader<Derived>::removeStock(std::shared_ptr<Stock> stock) {
    // We can only erase stocks that we own. 
    if (ownedStocks.contains(stock->getSymbol())){
        ownedStocks.erase(stock->getSymbol());
    }
    else {
        std::cout << "Seller doesn't own the stock :(" << std::endl;
    }
}

template <typename Derived>
void Trader<Derived>::placeOrder(const std::shared_ptr<Stock> stock, const OrderType order_tp, int quantity, double price) {
    if (order_tp == OrderType::SELL && !ownedStocks.contains(stock.get()->getSymbol())) {
        std::cerr << "Trader does not own the stock\n";
        return;
    }
    
    auto newOrder = std::make_shared<Order>(order_tp, traderID, stock, quantity, price);
    try {
        if (exchange == nullptr) { 
            std::cerr << "Trader has not joined an exchange\n";
            return;
        }
        exchange->addOrder(newOrder);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

template <typename Derived>
std::shared_ptr<Stock> Trader<Derived>::getStock(const std::string& symbol) const {
    return ownedStocks.get(symbol);
}

template <typename Derived>
void Trader<Derived>::handleOrder(const std::shared_ptr<Order> order, int bought_quantity) {

    double price = order->getPrice();

    double total = price * bought_quantity;
    std::shared_ptr<Stock> stock = order->getStock();

    OrderType type = order->getOrderType();
    switch(type) {
        case OrderType::BUY:
            buyStock(stock, total, bought_quantity);
            break;
        case OrderType::SELL:
            sellStock(stock, total, bought_quantity);
            break;
        default:
            std::cerr << "Invalid order type" << std::endl;
    }  
}

template <typename Derived>
void Trader<Derived>::buyStock(std::shared_ptr<Stock> stock, double total, int bought_quantity) {
    balance -= total;
    // Add the correct stock amount
    auto newStock = std::make_shared<Stock>(stock->getStockID(), stock->getSymbol(), bought_quantity);
    addStock(newStock);
}

template <typename Derived>
void Trader<Derived>::sellStock(std::shared_ptr<Stock> stock, double total, int bought_quantity) {
    balance += total;
    // only remove the stock if quantity goes to 0 or below
    if (stock->getNumberOfStocks() - bought_quantity <= 0) {
        removeStock(stock);
    }
    else {
        stock->removeStocks(bought_quantity);
    }
}

template <typename Derived>
bool Trader<Derived>::ownsStock(const std::string symbol) {
    return ownedStocks.contains(symbol);
}

#endif // TRADER_H