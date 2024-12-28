#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"


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

    // Stock google = Stock(1, "GOOGL", 100);
    // company1.addStock(google);
    // CHECK(company1.getStock("GOOGL") == google);
    // company1.removeStock(google);
    // CHECK_THROWS(company1.getStock("GOOGL") == google);
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
    Company company4(4, 100000, exchange, "Company4", "123");

    company3.createStock(1_ID, "CMPNY3"_SYM, 100_QTY);
    std::shared_ptr<Stock> stock = company3.getStock("CMPNY3");
    company3.placeOrder(stock, OrderType::SELL, 1, 200);
    company3.placeOrder(stock, OrderType::SELL, 1, 200);
    company4.placeOrder(stock, OrderType::BUY, 1, 150);
    company2.placeOrder(stock, OrderType::BUY, 1, 200);

    CHECK(company3.getBalance() == 100200);
    CHECK(company4.getBalance() == 100000);
    CHECK(company2.getBalance() == 0);

    company3.createStock(1_ID, "CMPNY3"_SYM, 100_QTY);
    //CHECK(company3.placeOrder(stock, OrderType::SELL, 1, 150));
    company3.createStock(1_ID, "CMPNY3"_SYM, 100_QTY);

    //CHECK(company3.placeOrder(stock, OrderType::SELL, 1, 150));
    //CHECK(company3.getBalance() == 100350);
    //CHECK(company4.getBalance() == 100000 - 150);

    // CHECK(company3.placeOrder(google, OrderType::BUY, 1, 100)); // ? der bliver printet at google ikke er på markedet, men den retunere stadig true. Er det rigtigt?
    // CHECK(company3.placeOrder(apple, OrderType::SELL, 1, 100));

    // Order buyorder(OrderType::BUY, 3, std::make_shared<Stock>(google), 100, 50.0);    
    // Order sellorder(OrderType::SELL, 3, std::make_shared<Stock>(google), 100, 50.0);

    // CHECK(company3.getBalance() == 100000);
    // company3.handleOrder(sellorder);
    // CHECK(company3.getBalance() == 100000 + (100 * 50.0));
    // company3.handleOrder(buyorder);
    // CHECK(company3.getBalance() == 100000);
    
}
