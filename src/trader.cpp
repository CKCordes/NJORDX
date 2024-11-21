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

int Trader::getTraderID() const {
    return traderID;
}

// The exchange will have removed the order, we just need to handle our part.
void Trader::handleOrder(const Order& order) {
    if (order.getOrderType() == OrderType::BUY) {
        if (order.getPrice() * order.getQuantity() > balance) {
            std::cerr << "Insufficient funds to place buy order" << std::endl;
            throw std::invalid_argument("Insufficient funds to place buy order");
        } else { // GITTE KODE!!
            balance -= order.getPrice() * order.getQuantity();
            auto it = std::find(ownedStocks.begin(), ownedStocks.end(), order.getStockID());
            if (it != ownedStocks.end()) {
                it->setQuantity(it->getQuantity() + order.getQuantity());
            } else {
                Stock newStock = exchange->getStock(order.getStockID());
                newStock.setQuantity(order.getQuantity());
                ownedStocks.push_back(newStock);
            }

        }
    } else if (order.getOrderType() == OrderType::SELL) { // GITTE KODE!!
        // Find the stock in the portfolio
        auto it = std::map::find(ownedStocks.begin(), ownedStocks.end(), order.getStockID()); // Virker det her?
        if (it != ownedStocks.end()) {
            // Check if the quantity is valid
            if (it->getQuantity() < order.getQuantity()) {
                std::cerr << "Insufficient stock to complete sell order" << std::endl;
                throw std::invalid_argument("Insufficient stock to place sell order");
            } else {
                balance += order.getPrice() * order.getQuantity();
                it->setQuantity(it->getQuantity() - order.getQuantity());
            }
        } else {
            std::cerr << "Stock not found in portfolio" << std::endl;
            throw std::invalid_argument("Stock not found in portfolio");
        }
    } else {
        std::cerr << "Invalid order type" << std::endl;
        throw std::invalid_argument("Invalid order type");
    }
}