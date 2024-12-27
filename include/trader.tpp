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

template <typename Derived>
class Trader : public ITrader {
    protected:
        int traderID;
        double balance;

        void buyStock(std::shared_ptr<Stock> stock, double total) override;
        void sellStock(std::shared_ptr<Stock> stock, double total) override;

        // Add currency to balance
    public:
        Njordx* exchange;

        OrderBook<std::string, std::shared_ptr<Stock>> ownedStocks;
        Trader(int, double, Njordx*);
        Trader(int, double);
        ~Trader() = default;

        void printTrader() const override;
        void displayPortfolio() override;

        int getTraderID() const override { return traderID; };
        double getBalance() const override;
        void setBalance(double amount) override;

        // Enable if the derived class is a company
        template <typename T = Derived>
        typename std::enable_if<std::is_same<T, Company>::value, void>::type
        createStock(int stockID, const std::string& symbol, int numberOfStocks) {
            auto newStock = std::make_shared<Stock>(stockID, symbol, numberOfStocks);
            ownedStocks.insert(symbol, newStock);
        }

        void addStock(std::shared_ptr<Stock> stock) override;
        void removeStock(std::shared_ptr<Stock>) override;
        
        Stock getStock(const std::string& symbol) const;

        bool placeOrder(const Stock&, const OrderType, int, double) override;

        void handleOrder(const Order&) override;

        void joinExchange(Njordx* exchange) override { this->exchange = exchange; };

};

// Delegating constructors
template <typename Derived>
Trader<Derived>::Trader(int id, double initialBalance) 
    : Trader<Derived>(id, initialBalance, nullptr) {}  

template <typename Derived>
Trader<Derived>::Trader(int id, double initialBalance, Njordx* exchange) 
    : traderID(id), balance(initialBalance), exchange(exchange) {}



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
bool Trader<Derived>::placeOrder(const Stock& stock, const OrderType order_tp, int quantity, double price) {
    Order newOrder = Order(order_tp, traderID, std::make_shared<Stock>(stock), quantity, price);
    try {
        if (exchange == nullptr) { 
            std::cerr << "Trader has not joined an exchange\n";
            return false;
        }
        exchange->addOrder(&newOrder);
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

template <typename Derived>
Stock Trader<Derived>::getStock(const std::string& symbol) const {
    return *(ownedStocks.get(symbol));
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
    addStock(stock);
}

template <typename Derived>
void Trader<Derived>::sellStock(std::shared_ptr<Stock> stock, double total) {
    balance += total;
    removeStock(stock);
}





#endif // TRADER_H