#include "doctest.h"
#include "stock.hpp"

TEST_CASE("Testing Stock class") {
    Stock stock(1, "AAPL", 100);
    CHECK(stock.getStockID() == 1);
    CHECK(stock.getSymbol() == "AAPL");
    CHECK(stock.getNumberOfStocks() == 100);
    stock.addStocks(200);
    CHECK(stock.getNumberOfStocks() == 200);
    stock.removeStocks(250);
    CHECK(stock.getNumberOfStocks() == 50);
    stock.displayInfo();
    Stock stock2(2, "GOOGL", 200);
    CHECK(stock == stock);
    CHECK_FALSE(stock == stock2);
}