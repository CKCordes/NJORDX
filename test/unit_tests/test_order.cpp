#include "doctest.h"
#include "order.hpp"

TEST_CASE("Testing Order class") {

    Stock stock(1_ID, "AAPL"_SYM, 100_QTY);

    Order order(OrderType::BUY, 1, std::make_shared<Stock>(stock), 10, 100.0);
    CHECK(order.getOrderType() == OrderType::BUY);
    CHECK(order.getTraderID() == 1);
    CHECK(order.getStockSymbol() == "AAPL");
    CHECK(order.getStockID() == 1);
    CHECK(order.getQuantity() == 10);
    CHECK(order.getPrice() == 100.0);
    CHECK(order.getIsFilled() == false);

    Stock stock2(2_ID, "GOOGL"_SYM, 200_QTY);

    Order order2(OrderType::SELL, 2, std::make_shared<Stock>(stock2), 20, 200.0);
    CHECK(order == order);
    CHECK_FALSE(order == order2);
    CHECK(true);
}