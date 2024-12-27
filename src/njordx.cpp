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
bool Njordx::addOrder(Order* order) noexcept {
    OrderType order_tp = order->getOrderType();
    switch (order_tp)
    {
    case OrderType::SELL:
        if (!validStocks.contains(order->getStockSymbol())){
        validStocks.insert(order->getStockSymbol(), order->getStockID());
        } 

        sellOrders.insert(order->getOrderID(), *order);

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
            buyOrders.insert(order->getOrderID(), *order);
            matchOrders();
            return true;
        } else {
          std::cout << "Stock " << order->getStockSymbol() << " is not on the market yet." << std::endl;
          return false;
        }
    default:
        throw std::invalid_argument("Unimplemented order type");
        return false;
    }
}

void Njordx::addTrader(ITrader* trader) noexcept {
    traders.push_back(trader);
}

// Functor
struct CompareOrder {
    bool operator()(const Order& buy, const Order& sell) const {
        return (buy.getStockID() == sell.getStockID()) && (buy.getPrice() >= sell.getPrice());
    }
};

// Matches the 
void Njordx::matchOrders() { 
    using namespace std::placeholders;
    // USING STD::BIND WITH LAMBDA?!?!?!?!?!?!?!?!?! 
    const CompareOrder OrderComparator = CompareOrder();
    auto match = std::bind([this, OrderComparator](Order& buy, Order& sell) {
        if (OrderComparator(buy, sell) && !(buy.getIsFilled() || sell.getIsFilled())) {
            int buyer_id = buy.getTraderID();
            int seller_id = sell.getTraderID();

            // Find buyer and seller
            auto buyer = std::find_if(traders.begin(), traders.end(), [buyer_id](ITrader* trader) {
                return trader->getTraderID() == buyer_id;
            });
            auto seller = std::find_if(traders.begin(), traders.end(), [seller_id](ITrader* trader) {
                return trader->getTraderID() == seller_id;
            });

            if (buyer != traders.end() && seller != traders.end()) {
                (*buyer)->handleOrder(buy);
                (*seller)->handleOrder(sell);
                buy.setIsFilled(true);
                sell.setIsFilled(true);
            } 
        }
    }, _1, _2);
    for (auto& buy_order : buyOrders) {
        if (buy_order.value.getIsFilled()) {
            continue;
        }
       for (auto& sell_order : sellOrders) {
              if (sell_order.value.getIsFilled()) {
                continue;
              }
           match(std::ref(buy_order.value), std::ref(sell_order.value));
       }
    }
}

//Display orderbooks
void Njordx::displayOrderBook(const OrderType type) const {
    if (type == OrderType::SELL) {
        throw std::logic_error("Not implemented yet");
    } else if (type == OrderType::BUY) {
        throw std::logic_error("Not implemented yet");
    } else {
        throw std::invalid_argument("Invalid order type");
    }
}

