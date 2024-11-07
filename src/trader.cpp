#include "trader.hpp"

double Trader::getBalance() const {
    return balance;
}

void Trader::setBalance(double amount) {
    balance = amount;
}

void Trader::addStock(const Stock& stock) {
    ownedStocks.push_back(stock);
}

void Trader::removeStock(const Stock& stock) {
    auto it = std::find(ownedStocks.begin(), ownedStocks.end(), stock);
    if (it != ownedStocks.end()) {
        ownedStocks.erase(it);
    } else {
        throw std::invalid_argument("Stock not found in portfolio");
    }
}

Order Trader::placeBuyOrder(const Stock& stock, int quantity, double price) {
    int orderID = 1; // Placeholder for now
    std::cout << "CHANGE THE STUPID ORDER ID!!" << std::endl;
    Order newOrder = Order(orderID, OrderType::BUY, traderID, stock.getStockID(), quantity, price);
    return newOrder;
}

Order Trader::placeSellOrder(const Stock& stock, int quantity, double price) {
    int orderID = 1; // Placeholder for now
    std::cout << "CHANGE THE STUPID ORDER ID!!" << std::endl;
    Order newOrder = Order(orderID, OrderType::SELL, traderID, stock.getStockID(), quantity, price);
    return newOrder;
}