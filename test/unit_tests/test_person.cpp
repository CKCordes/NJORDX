#include "doctest.h"
#include "person.tpp"
#include "njordx.hpp"

TEST_CASE("Testing company class"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    // Constructing person1 and validating
    Person person1(1, 100, exchange, "Person1", "12345");
    CHECK(person1.getBalance() == 100); 
    person1.setBalance(200);
    CHECK(person1.getBalance() == 200);  
    CHECK(person1.getTraderID() == 1);
    CHECK(person1.getName() == "Person1");
    CHECK(person1.getSSN() == "12345");

    // Constructing person2 and validating    
    Person person2(2, 300, "Person2", "6789");
    CHECK(person2.getBalance() == 300);
    person2.joinExchange(exchange);

    person2.displayPortfolio();

}