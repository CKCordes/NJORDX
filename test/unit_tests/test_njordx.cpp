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

    Order buy_order(1, OrderType::BUY, 1, std::make_shared<Stock>(stock), 10, 100.0);
    Order sell_order(2, OrderType::SELL, 2, std::make_shared<Stock>(stock), 10, 100.0);
    njordx.addBuyOrder(&buy_order);
    njordx.addSellOrder(&sell_order);
}

TEST_CASE("Adding traders to exchange") {
    Njordx njordx;
    Company company1(1, 100, &njordx, "Company1", "12345678");
    Company company2(2, 100, &njordx, "Company2", "87654321");

    njordx.addTrader(&company1);
    njordx.addTrader(&company2);
}

TEST_CASE("Testing matching of orders") {
    Njordx njordx;
    std::cout << "1" << std::endl;
    Stock stock(1, "AAPL", 100);

    Order buy_order(1, OrderType::BUY, 1, std::make_shared<Stock>(stock), 10, 100.0);
    Order sell_order(2, OrderType::SELL, 2, std::make_shared<Stock>(stock), 10, 100.0);

    njordx.addBuyOrder(&buy_order);
    njordx.addSellOrder(&sell_order);

    Company company1(1, 100, &njordx, "Company1", "12345678");
    Company company2(2, 100, &njordx, "Company2", "87654321");

    njordx.addTrader(&company1);
    njordx.addTrader(&company2);

    std::cout << "4" << std::endl;
    company2.placeSellOrder(stock, 3, 5);
    std::cout << "5" << std::endl;
    company1.placeBuyOrder(stock, 1, 5);
    njordx.matchOrders();
}