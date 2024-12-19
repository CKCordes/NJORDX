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
    std::cout << "Først er vi her" << std::endl;
    Company company2(2, 200, "Company2", "87654321");
    std::cout << "Nu er vi her" << std::endl;
    CHECK(company2.getBalance() == 200);

    Stock apple = Stock(1, "AAPL", 100);
    company2.createStock(1, "AAPL", 100); 
    CHECK(company2.getStock("AAPL") == apple);
    company2.displayPortfolio();
}

TEST_CASE("Testing company's order related methods"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    Company company3(3, 100000, exchange, "Company3", "123");
    Company company4(4, 100000, exchange, "Company4", "123");
    //Stock apple = Stock(1, "AAPL", 100);
    // Stock google = Stock(2, "GOOGL", 200);
    // company3.addStock(apple);
    // company3.addStock(google);
    company3.createStock(1, "CMPNY3", 100);
    
    Stock stock = company3.getStock("CMPNY3");
    CHECK(company3.placeOrder(stock, OrderType::SELL, 1, 100));
    CHECK(company4.placeOrder(stock, OrderType::BUY, 1, 100));
    
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
