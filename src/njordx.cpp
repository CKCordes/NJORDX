#include "njordx.hpp"
#include <algorithm>
#include <thread>
#include <fstream>
#include <iostream>
#include <iterator>
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
//Njordx::Njordx() : buyOrders{}, sellOrders{} {}

// Method to add a buy order to the Njordx
void Njordx::addBuyOrder(const Order* order) {
    return;
}

// Method to add a sell order to the Njordx
void Njordx::addSellOrder(const Order* order) {
    return;
}

// Method to match buy and sell orders
void Njordx::matchOrders() {
    return;
}

//Display orderbooks
void Njordx::displayOrderBook() const {
    /*std::ostream_iterator<Order> out_it (std::cout, "\n");
    // Buy orders
    copy(buyOrders.begin(), buyOrders.end(), out_it); // Wtf det her bør ik virk
    // Sell orders
    copy(sellOrders.begin(), sellOrders.end(), out_it); // Wtf det her bør ik virk
    */
   return;
}

