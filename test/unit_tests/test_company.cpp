#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"


// Constructing two company1 and validating
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
    Stock google = Stock(1, "GOOGL", 100);
    company1.addStock(google);
    CHECK(company1.getStock("GOOGL") == google);
    company1.removeStock(google);
    CHECK_THROWS(company1.getStock("GOOGL") == google);
}

TEST_CASE("Testing delegating company constructors, joinExchange() and createStock()"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();
    
    // Constructing company2 and validating    
    Company company2(2, 200, "Company2", "87654321");
    CHECK(company2.getBalance() == 200);
    company2.joinExchange(exchange);

    company2.createStock(1, "AAPL", 100);
    company2.displayPortfolio();
}

// TODO: lav denne test
TEST_CASE("Testing company's order related methods"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    // Constructing company3
    Company company3(3, 300, exchange, "Company3", "123");
}