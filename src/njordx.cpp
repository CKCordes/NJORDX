#include "njordx.hpp"
#include <algorithm>
#include <thread>
#include <fstream>
#include <iostream>
#include <iterator>
#include <variant>

// Constructor
Njordx::Njordx() : buyOrders(), sellOrders(), validStocks() {}

/* Inserting in StockOrderBook, has a strong guarentee */
void Njordx::addOrder(std::shared_ptr<Order> order) noexcept {
    OrderType order_tp = order->getOrderType();
    switch (order_tp)
    {
    case OrderType::SELL:
        if (!validStocks.contains(order->getStockSymbol())){
        validStocks.insert(order->getStockSymbol(), order->getStockID());
        }
        sellOrders.insert(order->getOrderID(), order);
        // Match orders
        matchOrders();
        return;

    case OrderType::BUY:
        if (validStocks.contains(order->getStockSymbol())) {
            buyOrders.insert(order->getOrderID(), order);
            matchOrders();
        } else {
          std::cout << "Stock " << order->getStockSymbol() << " is not on the market yet." << std::endl;
        }
        return;
        
    default:
        std::cerr << "Invalid order type" << std::endl;
        return;
    }
}

void Njordx::addTrader(ITrader* trader) noexcept {
    traders.push_back(trader);
}

// Functor
struct CompareOrder {
    bool operator()(const std::shared_ptr<Order> buy, const std::shared_ptr<Order> sell) const {
        //return (buy->getStockID() == sell->getStockID()) && (buy->getPrice() >= sell->getPrice());
        return (buy->getStockSymbol() == sell->getStockSymbol()) && (buy->getPrice() >= sell->getPrice() && buy->getQuantity() == sell->getQuantity());
    }
};

// Matches the 
void Njordx::matchOrders() { 
    using namespace std::placeholders;
    // USING STD::BIND WITH LAMBDA?!?!?!?!?!?!?!?!?! Who is this guy?
    const CompareOrder OrderComparator = CompareOrder();
    auto match = std::bind([this, OrderComparator](std::shared_ptr<Order> buy, std::shared_ptr<Order> sell) {
        if (OrderComparator(buy, sell) && !(buy->getIsFilled() || sell->getIsFilled())) {
            int buyer_id = buy->getTraderID();
            int seller_id = sell->getTraderID();

            // Find buyer and seller
            auto buyer = std::find_if(traders.begin(), traders.end(), [buyer_id](ITrader* trader) {
                return trader->getTraderID() == buyer_id;
            });
            auto seller = std::find_if(traders.begin(), traders.end(), [seller_id](ITrader* trader) {
                return trader->getTraderID() == seller_id;
            });
            if (buyer == traders.end() || seller == traders.end()) {
                std::cerr << (buyer == traders.end() ? "Buyer" : "Seller") << " not found" << std::endl;
            } else {
                buy->setPrice(sell->getPrice());
                int quantity = buy->getQuantity();
                (*buyer)->handleOrder(buy, quantity);
                (*seller)->handleOrder(sell, quantity);
                buy->setIsFilled(true);
                sell->setIsFilled(true);
            } 
        }
    }, _1, _2);
    for (auto& buy_order : buyOrders) {
        if (buy_order.value.get()->getIsFilled()) {
            continue;
        }
       for (auto& sell_order : sellOrders) {
            if (sell_order.value.get()->getIsFilled()) {
              continue;
            }
            match(buy_order.value, sell_order.value);
       }
    }
}

//Display orderbooks
void Njordx::displayOrderBook(const OrderType type) {
    auto& orders = (type == OrderType::SELL) ? sellOrders : buyOrders;
    std::string orderTypeStr = (type == OrderType::SELL) ? "Sell" : "Buy";

    std::cout << orderTypeStr << " orders:\n";
    for (auto& order : orders) {
        std::cout << "Stock: " << order.value->getStockSymbol() 
                  << ", price: " << order.value->getPrice() 
                  << ", filled: " << order.value->getIsFilled()
                  << ", quantity: " << order.value->getQuantity() << std::endl;
    }
}

void Njordx::displayAvailableStocks() { // missing const
    std::cout << "Available stocks: ";
    for (auto stock : validStocks) {
        std::cout << stock.key << " ";
    }
    std::cout << std::endl;
}

