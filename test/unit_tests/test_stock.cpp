#include "doctest.h"
#include "stock.hpp"

TEST_CASE("Testing Stock class") {
    Stock stock(1, "AAPL", 100.0);
    CHECK(stock.getStockID() == 1);
    CHECK(stock.getSymbol() == "AAPL");
    CHECK(stock.getPrice() == 100.0);
    stock.setPrice(200.0);
    CHECK(stock.getPrice() == 200.0);
    stock.displayInfo();
    Stock stock2(2, "GOOGL", 200.0);
    CHECK(stock == stock);
    CHECK_FALSE(stock == stock2);
}