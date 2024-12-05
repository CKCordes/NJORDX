#include "doctest.h"
#include "order.hpp"

TEST_CASE("Testing Order class") {

    Stock stock(1, "AAPL", 100);

    Order order(OrderType::BUY, 1, std::make_shared<Stock>(stock), 10, 100.0);
    //CHECK(order.getOrderID() < 1000);
    CHECK(order.getOrderType() == OrderType::BUY);
    CHECK(order.getTraderID() == 1);
    CHECK(order.getStockSymbol() == "AAPL");
    CHECK(order.getStockID() == 1);
    CHECK(order.getQuantity() == 10);
    CHECK(order.getPrice() == 100.0);
    CHECK(order.getIsFilled() == false);

    //order.setStockID(1);
    //order.setIsFilled(true);
    //CHECK(order.getStockID() == 1);
    //CHECK(order.getIsFilled() == true);
    //order.displayOrderDetails();

    Stock stock2(2, "GOOGL", 200);

    Order order2(OrderType::SELL, 2, std::make_shared<Stock>(stock2), 20, 200.0);
    CHECK(order == order);
    CHECK_FALSE(order == order2);
    CHECK(true);
}