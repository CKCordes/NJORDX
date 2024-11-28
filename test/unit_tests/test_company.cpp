#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"

TEST_CASE("Testing company class"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    // Constructing two company1 and validating
    Company company1(1, 100, exchange, "Company1", "12345678");
    CHECK(company1.getBalance() == 100); 
    company1.setBalance(200);
    CHECK(company1.getBalance() == 200);  

    // Constructing company2 and validating    
    Company company2(2, 200, "Company2", "87654321");
    CHECK(company2.getBalance() == 200);
    company2.joinExchange(exchange);

    company2.createStock(1, "AAPL", 100);
    //company2.displayPortfolio();
}