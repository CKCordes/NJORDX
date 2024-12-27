#include "doctest.h"
#include "stock.hpp"

TEST_CASE("Testing Stock class") {
    Stock stock(1_ID, "AAPL"_SYM, 100_QTY);
    CHECK(stock.getStockID() == 1);
    CHECK(stock.getSymbol() == "AAPL");
    CHECK(stock.getNumberOfStocks() == 100);
    stock.addStocks(200);
    CHECK(stock.getNumberOfStocks() == 300);
    stock.removeStocks(250);
    CHECK(stock.getNumberOfStocks() == 50);
    stock.displayInfo();
    Stock stock2(2_ID, "GOOGL"_SYM, 200_QTY);
    CHECK(stock == stock);
    CHECK_FALSE(stock == stock2);
}