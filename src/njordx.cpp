#include "njordx.hpp"
#include <algorithm>
#include <thread>
#include <fstream>
#include <iostream>
#include <iterator>
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

/* Gode ting at have med i denne klasse
Order* order = nullptr;

auto order = Order(1, OrderType::BUY, 1, 1, 100, 50.0);
decltype(order) anotherOrder = order;

std::unique_ptr<Order> order = std::make_unique<Order>(1, OrderType::BUY, 1, 1, 100, 50.0);

for (auto it = buyOrders.begin(); it != buyOrders.end(); ++it) {
    it->displayOrderDetails();
}

std::sort(buyOrders.begin(), buyOrders.end(), [](const Order& a, const Order& b) {
    return a.getPrice() > b.getPrice();
});

if (order.getQuantity() <= 0) {
    throw std::invalid_argument("Quantity must be positive");
}

if constexpr (std::is_integral_v<int>) {
    // Do something
}

Order newOrder = std::move(order);

 */


// Constructor
Njordx::Njordx() : buyOrders(), sellOrders(), validStocks() {}

/* Inserting in StockOrderBook, has a strong guarentee */

bool Njordx::addSellOrder(Order* order) const noexcept {
    if (!validStocks.contains(order->getStockSymbol())){
      validStocks.insert(order->getStockSymbol(), order->getStockID());
    } 
    sellOrders.insert(order->getOrderID(), *order);
    return true;
}

bool Njordx::addBuyOrder(Order* order) const noexcept {
    if (validStocks.contains(order->getStockSymbol())) {
        int stockID = validStocks.get(order->getStockSymbol());
        order->setStockID(stockID);
        buyOrders.insert(order->getOrderID(), *order);
        return true;
      } 
      else {
        std::cout << "Stock not valid" << std::endl;
        return false;
      }
}

// Method to match buy and sell orders
Order Njordx::matchOrders() {
    /* USING STD::BIND WITH LAMBDA?!?!?!?!?!?!?!?!?! */
    auto match = std::bind([](const Order& buy, const Order& sell) {
        return buy.getPrice() >= sell.getPrice();
    }, std::placeholders::_1, std::placeholders::_2);

    for (auto buy_order : buyOrders) {
        for (auto sell_order : sellOrders) {
            if (true) { //match(buy_order, sell_order)
                sell_order = buy_order;
                return buy_order.value;
            }
        }
    }
    return Order(1, OrderType::BUY, 1, 1, 1, 1.0);
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

