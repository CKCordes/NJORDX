#include "doctest.h"
#include "njordx.hpp"
#include "order.hpp"
#include "company.tpp"

TEST_CASE("Testing init of NJORDX"){
    Njordx njordx;
}
TEST_CASE("Adding orders to exchange") {
    Njordx njordx;
    Stock stock(1, "AAPL", 100);

    Order buy_order(OrderType::BUY, 1, std::make_shared<Stock>(stock), 10, 100.0);
    Order sell_order(OrderType::SELL, 2, std::make_shared<Stock>(stock), 10, 100.0);
    njordx.addSellOrder(&sell_order);
    njordx.addBuyOrder(&buy_order);
}

TEST_CASE("Adding traders to exchange") {
    Njordx njordx;
    Company company1(1, 100, &njordx, "Company1", "12345678");
    Company company2(2, 100, &njordx, "Company2", "87654321");

    njordx.addTrader(&company1);
    njordx.addTrader(&company2);
}

TEST_CASE("Testing matching of orders") {
    //We should ONLY create and place orders through traders, not directly to the exchange
    //Order sell_order(OrderType::SELL, 2, std::make_shared<Stock>(stock), 10, 100.0);
    //Order buy_order(OrderType::BUY, 1, std::make_shared<Stock>(stock), 10, 100.0);
    //njordx.addSellOrder(&sell_order);
    //njordx.addBuyOrder(&buy_order);

    Njordx njordx;
    Stock stock(1, "AAPLE", 100);

    Company company1(1, 100, &njordx, "Company1", "12345678");
    Company company2(2, 100, &njordx, "Company2", "87654321");

    njordx.addTrader(&company1);
    njordx.addTrader(&company2);
/*
    company2.createStock(1, "AAPLE", 100);
    CHECK(company2.ownedStocks.contains("AAPLE"));
    company2.placeSellOrder(stock, 3, 5);
    company1.placeBuyOrder(stock, 1, 5);
    njordx.matchOrders();
*/
}