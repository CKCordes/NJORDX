#include "doctest.h"
#include "person.tpp"
#include "njordx.hpp"

TEST_CASE("Testing initialization of person class and getters and setters"){
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

    Stock google = Stock(1, "GOOGL", 100);
    person1.addStock(google);
    CHECK(person1.getStock("GOOGL") == google);
    person1.removeStock(google);
    CHECK_THROWS(person1.getStock("GOOGL") == google);
}

TEST_CASE("Testing delegating person constructors, joinExchange() and displayPortfolio()"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();
    
    // Constructing person2 and validating    
    Person person2(2, 300, "Person2", "6789");
    CHECK(person2.getBalance() == 300);
    person2.joinExchange(exchange);

    person2.displayPortfolio();
}

// TODO: lav denne test
TEST_CASE("Testing person's order related methods"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    // Constructing company3
    Person person3(3, 300, exchange, "person3", "123");
}
