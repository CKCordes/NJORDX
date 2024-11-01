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
Njordx::Njordx() : buyOrders(16), sellOrders(16) {}

// Method to add a sell order to the Njordx
void Njordx::addOrder(const OrderType type, const Order* order) {
    if (type == OrderType::SELL) {
      sellOrders.insert(order->getOrderID(), *order);
    } else if (type == OrderType::BUY) {
      buyOrders.insert(order->getOrderID(), *order);
    } else {
        throw std::invalid_argument("Invalid order type");
    }
}

// Method to match buy and sell orders
Order Njordx::matchOrders() {
    throw std::logic_error("Not implemented yet");
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

