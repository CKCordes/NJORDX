#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"

#include <iostream>



TEST_CASE("Testing initialization of company classes and getters and setters"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    Company company1(1, 100, exchange, "Company1", "12345678");
    CHECK(company1.getBalance() == 100); 
    company1.setBalance(200);
    CHECK(company1.getBalance() == 200);  
    CHECK(company1.getTraderID() == 1);
    CHECK(company1.getCompanyName() == "Company1");
    CHECK(company1.getRegistrationNumber() == "12345678");
}

TEST_CASE("Testing delegating company constructors, joinExchange() and createStock()"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();
    Company company2(2, 200, "Company2", "87654321");
    CHECK(company2.getBalance() == 200);
    company2.joinExchange(exchange);

    company2.createStock(1_ID, "AAPL"_SYM, 100_QTY); 
    CHECK(company2.ownsStock("AAPL"));
}

TEST_CASE("Testing company's order related methods"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();
    Company company2(2, 200, exchange, "Company2", "87654321");
    Company company3(3, 100000, exchange, "Company3", "123");
    Company company4(4, 100000, exchange, "Company4", "1234");

    company3.createStock(1_ID, "CMPNY3"_SYM, 100_QTY);
    auto stockOpt = company3.getStock("CMPNY3");
    CHECK(stockOpt.has_value());
    auto stock = stockOpt.value();
    
    // Order shouldn't go through
    company3.placeOrder(stock, OrderType::SELL, 1, 200);
    company3.placeOrder(stock, OrderType::SELL, 1, 200);
    // Order should go through
    company4.placeOrder(stock, OrderType::BUY, 1, 150);
    company2.placeOrder(stock, OrderType::BUY, 1, 200);

    CHECK(company3.getBalance() == 100200);
    CHECK(company4.getBalance() == 100000);
    CHECK(company2.getBalance() == 0);  
}
