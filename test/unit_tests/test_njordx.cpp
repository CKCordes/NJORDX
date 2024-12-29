#include "doctest.h"
#include "njordx.hpp"
#include "order.hpp"
#include "company.tpp"
#include "person.tpp"

TEST_CASE("Testing init of NJORDX"){
    Njordx njordx;
}
TEST_CASE("Adding orders to exchange") {
    Njordx njordx;
    auto stock = std::make_shared<Stock>(1_ID, "AAPL"_SYM, 100_QTY);

    auto buy_order = std::make_shared<Order>(OrderType::BUY, 1, stock, 10, 100.0);
    auto sell_order = std::make_shared<Order>(OrderType::SELL, 2, stock, 10, 100.0);
    njordx.addOrder(sell_order);
    njordx.addOrder(buy_order);
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
    //njordx.addOrder(&sell_order);
    //njordx.addOrder(&buy_order);

    Njordx njordx;
    auto stock = std::make_shared<Stock>(1_ID, "AAPLE"_SYM, 100_QTY);

    Company company1(1, 100, "Company1", "12345678");
    company1.joinExchange(&njordx);
    //Company company2(2, 100, &njordx, "Company2", "87654321");
    Person person1(3, 100, &njordx, "Person1", "12345678");

    company1.createStock(1, "AAPLE", 100);
    CHECK(company1.ownsStock("AAPLE"));
    company1.placeOrder(stock, OrderType::SELL, 3, 5);
    person1.placeOrder(stock, OrderType::BUY, 1, 5);

}