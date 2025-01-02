#ifndef TRADER_H
#define TRADER_H


#include <vector>
#include <string>
#include <iostream>
#include <type_traits>
#include <optional>
#include <memory>
#include "njordx.hpp"
#include "stockOrderBook.tpp"
#include "ITrader.hpp"

class Company; // Forward declaration
class Person; // Forward declaration

// Fixed traits and value traits for calculating total in handleOrder
template <typename T>
struct TotalTraits;

template <>
struct TotalTraits<double> {
    typedef double TotalType;
    static TotalType zero() { return static_cast<double>(0); }
};

template <>
struct TotalTraits<int> {
    typedef double TotalType;
    static TotalType zero() { return static_cast<double>(0); }
};

template <typename T>
double calcTotal(T price, int quantity) {
    typedef typename TotalTraits<T>::TotalType TotalType;
    TotalType total = TotalTraits<T>::zero();
    total = price * quantity;
    return total;
}

// Variadic templated function for notifying about errors
template <typename... Args>
void notifyTrader(const std::string& eventType, Args... args) {
    std::cerr << "Error: [" << eventType << "] ";
    (std::cerr << ... << args) << std::endl;
}

template <typename Derived>
class Trader : public ITrader {
    protected:
        int traderID;
        double balance;

        void buyStock(std::shared_ptr<Stock> stock, double total, int bought_quantity) override;
        void sellStock(std::shared_ptr<Stock> stock, double total, int bought_quantity) override; 
        void addStock(std::shared_ptr<Stock> stock);
        void removeStock(std::shared_ptr<Stock> stock);

        OrderBook<std::string, std::shared_ptr<Stock>> ownedStocks; // todo: CHANGE TO PROTECTED AGAIN!
        
        // todo: Add currency to balance


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
            ownedStocks.insertStock(symbol, newStock);
        }

        std::optional<std::shared_ptr<Stock>> getStock(const std::string& symbol) const;

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
    ownedStocks.insertStock(stock->getSymbol(), stock);
}

template <typename Derived>
void Trader<Derived>::removeStock(std::shared_ptr<Stock> stock) {
    // We can only erase stocks that we own. 
    if (ownedStocks.contains(stock->getSymbol())){
        ownedStocks.erase(stock->getSymbol());
    }
    else {
        notifyTrader("RemoveStock", "Trader does not own stock ", stock->getSymbol());
    }
}

template <typename Derived>
void Trader<Derived>::placeOrder(const std::shared_ptr<Stock> stock, const OrderType order_tp, int quantity, double price) {
    if (exchange == nullptr) { 
        notifyTrader("PlaceOrder", "Trader is not connected to an exchange");
        return;
    }
    if (order_tp == OrderType::SELL) {
        auto ownedStock = ownedStocks.get(stock->getSymbol());
        if (!ownedStock) {
            notifyTrader("PlaceOrder", "Trader does not own stock ", stock->getSymbol());
            return;
        }
        if (ownedStock.value()->getNumberOfStocks() < quantity) {
            notifyTrader("PlaceOrder", "Trader does not own enough of the stock");
            return;
        }
    }
    
    auto newOrder = std::make_shared<Order>(order_tp, traderID, stock, quantity, price);
    exchange->addOrder(newOrder);
}

template <typename Derived>
std::optional<std::shared_ptr<Stock>> Trader<Derived>::getStock(const std::string& symbol) const {
    return ownedStocks.get(symbol);
}

template <typename Derived>
void Trader<Derived>::handleOrder(const std::shared_ptr<Order> order, int bought_quantity) {

    double price = order->getPrice();

    double total = calcTotal(price, bought_quantity);
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