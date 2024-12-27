#include "njordx.hpp"
#include <algorithm>
#include <thread>
#include <fstream>
#include <iostream>
#include <iterator>
#include <variant>
// ----------------------------NOTER--------------------------------//
// NJORDX bør være singleton

// Vi skal lave en valid aktie list som børsen kan kigge i om en buy order er valid

// en trader (company) opretter en stock (kun sin egen) og sætter til salg. Denne ryger i valid og sellorder
// En trader (person) opretter en buy order med stock navn. Når denne bliver oprettet, spørger den børsen om stockID og om valid
// hvis valid, tilføjes order til børsens buyOrders.

// Når børsen matcher en buy og sell order, skal de begge fjernes fra buyOrders og sellOrders
// Køber mister penge (SALGSPRISEN) sælger får salgsprisen på balance

// traders har en "pending orderbook"
// --------------------------NOTER SLUT-----------------------------//

// Constructor
Njordx::Njordx() : buyOrders(), sellOrders(), validStocks() {}

/* Inserting in StockOrderBook, has a strong guarentee */
bool Njordx::addOrder(std::shared_ptr<Order> order) noexcept {
    OrderType order_tp = order->getOrderType();
    switch (order_tp)
    {
    case OrderType::SELL:
        if (!validStocks.contains(order->getStockSymbol())){
        validStocks.insert(order->getStockSymbol(), order->getStockID());
        } 

        sellOrders.insert(order->getOrderID(), order);

        // Match orders
        try {
            matchOrders();
        }
        catch (const std::exception& e) {
            std::cerr << "Encountered error in matchOrders()" <<  e.what() << std::endl;
            return false;
        }
        return true;
    case OrderType::BUY:
        if (validStocks.contains(order->getStockSymbol())) {
            buyOrders.insert(order->getOrderID(), order);
            matchOrders();
            return true;
        } else {
          std::cout << "Stock " << order->getStockSymbol() << " is not on the market yet." << std::endl;
          return false;
        }
    default:
        std::cerr << "Invalid order type" << std::endl;
        return false;
    }
}

void Njordx::addTrader(ITrader* trader) noexcept {
    traders.push_back(trader);
}

// Functor
struct CompareOrder {
    bool operator()(const std::shared_ptr<Order> buy, const std::shared_ptr<Order> sell) const {
        //return (buy->getStockID() == sell->getStockID()) && (buy->getPrice() >= sell->getPrice());
        return (buy->getStockSymbol() == sell->getStockSymbol()) && (buy->getPrice() >= sell->getPrice());

    }
};

// Matches the 
void Njordx::matchOrders() { 
    using namespace std::placeholders;
    // USING STD::BIND WITH LAMBDA?!?!?!?!?!?!?!?!?! Who is this guy?
    const CompareOrder OrderComparator = CompareOrder();
    auto match = std::bind([this, OrderComparator](std::shared_ptr<Order> buy, std::shared_ptr<Order> sell) {
        if (OrderComparator(buy, sell) && !(buy->getIsFilled() || sell->getIsFilled())) {
            std::cout << "Matching orders" << std::endl;
            int buyer_id = buy->getTraderID();
            int seller_id = sell->getTraderID();

            // Find buyer and seller
            auto buyer = std::find_if(traders.begin(), traders.end(), [buyer_id](ITrader* trader) {
                return trader->getTraderID() == buyer_id;
            });
            auto seller = std::find_if(traders.begin(), traders.end(), [seller_id](ITrader* trader) {
                return trader->getTraderID() == seller_id;
            });
            if (buyer == traders.end()) {
                std::cerr << "Buyer not found" << std::endl;
            }
            if (seller == traders.end()) {
                std::cerr << "Seller not found" << std::endl;
            }
            if (buyer != traders.end() && seller != traders.end()) {
                (*buyer)->handleOrder(buy);
                (*seller)->handleOrder(sell);
                std::cout << "Matched order" << std::endl;
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

//Display orderbooks. Hallo en eller anden fix det her lort, der er så meget kopiering
void Njordx::displayOrderBook(const OrderType type) { // missing const
    if (type == OrderType::SELL) {
        std::cout << "Sell orders:\n";
        for (auto order : sellOrders) {
            std::cout << "Stock: " << order.value.get()->getStockSymbol() << ", price: " << order.value.get()->getPrice() << " filled: " << order.value.get()->getIsFilled() << std::endl;
        }
    } else if (type == OrderType::BUY) {
        std::cout << "Buy orders:\n";
        for (auto order : buyOrders) {
            std::cout << "Stock: " << order.value.get()->getStockSymbol() << ", price: " << order.value.get()->getPrice() << " filled: " << order.value.get()->getIsFilled() << std::endl;
        }
    } else {
        throw std::invalid_argument("Invalid order type");
    }
}

void Njordx::displayAvailableStocks() { // missing const
    std::cout << "Available stocks: ";
    for (auto stock : validStocks) {
        std::cout << stock.key << " ";
    }
    std::cout << std::endl;
}

