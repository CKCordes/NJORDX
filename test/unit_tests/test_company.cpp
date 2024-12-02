#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"

TEST_CASE("Creating company w/o xchange"){
    // Constructing two company1 and validating
    Company company1(1, 100, "Company1", "12345678");
    CHECK(company1.getBalance() == 100); 
    company1.setBalance(200);
    CHECK(company1.getBalance() == 200);  

    // Constructing company2 and validating    
    Company company2(2, 200, "Company2", "87654321");
    CHECK(company2.getBalance() == 200);

    company2.createStock(1, "AAPL", 100);
}

TEST_CASE("Creating and placing orders") {
    Njordx njordx;
    Stock stock(1, "AAPLE", 100);

    Company company1(1, 100, &njordx, "Company1", "12345678");

    company1.addStock(stock);
    company1.placeOrder(stock, OrderType::SELL, 1, 10);
}

TEST_CASE("Placing invalid order") {
    Stock stock(1, "AAPLE", 100);

    Company company1(1, 100, "Company1", "12345678");

    company1.addStock(stock);
    bool order_res = company1.placeOrder(stock, OrderType::SELL, 1, 10);
    CHECK_FALSE(order_res);
}