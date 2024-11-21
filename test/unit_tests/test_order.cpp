#include "doctest.h"
#include "order.hpp"

TEST_CASE("Testing Order class") {
    Order order(1, OrderType::BUY, 1, "AAPL", 10, 100.0);
    CHECK(order.getOrderID() == 1);
    CHECK(order.getOrderType() == OrderType::BUY);
    CHECK(order.getTraderID() == 1);
    CHECK(order.getStockSymbol() == "AAPL");
    CHECK(order.getStockID() == -1);
    CHECK(order.getQuantity() == 10);
    CHECK(order.getPrice() == 100.0);
    CHECK(order.getIsFilled() == false);

    
    order.setStockID(1);
    order.setIsFilled(true);
    CHECK(order.getStockID() == 1);
    CHECK(order.getIsFilled() == true);
    order.displayOrderDetails();

    Order order2(2, OrderType::SELL, 2, "GOOGL", 20, 200.0);
    CHECK(order == order);
    CHECK_FALSE(order == order2);
}