#include "doctest.h"
#include "person.tpp"
#include "company.tpp"
#include "njordx.hpp"

#include <iostream>

TEST_CASE("Testing initialization of person class and getters and setters"){
    std::cout << "Person tests:";
    
    // Constructing a new exchange
    Njordx* exchange = new Njordx();


    Person person1(1, 100, exchange, "Person1", "12345");
    CHECK(person1.getBalance() == 100); 
    person1.setBalance(200);
    CHECK(person1.getBalance() == 200);  
    CHECK(person1.getTraderID() == 1);
    CHECK(person1.getName() == "Person1");
    CHECK(person1.getSSN() == "12345");

    std::cout << std::endl;
}

TEST_CASE("Testing delegating person constructors, joinExchange() and displayPortfolio()"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();
      
    Person person1(1, 300, "Person1", "6789");
    CHECK(person1.getBalance() == 300);
    CHECK(person1.getTraderID() == 1);
    CHECK(person1.getName() == "Person1");
    CHECK(person1.getSSN() == "6789");
    person1.displayPortfolio();

    Person person2(2, 300, exchange, "Person2", "6789");
    person2.joinExchange(exchange);
    CHECK(person2.getBalance() == 300);
    CHECK(person2.getTraderID() == 2);
    CHECK(person2.getName() == "Person2");
    CHECK(person2.getSSN() == "6789");
    person2.displayPortfolio();

    std::cout << std::endl;
}

TEST_CASE("Testing notifyTrader"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    auto apple = std::make_shared<Stock>(1_ID, "AAPL"_SYM, 100_QTY);

    auto person1 = std::make_shared<Person>(1, 300, "Person1", "6789");

    person1->placeOrder(apple, OrderType::SELL, 100, 100); // Should fail as person1 isn't connected to an exchange

    person1->joinExchange(exchange);

    person1->placeOrder(apple, OrderType::SELL, 100, 100); // Should fail as person1 doesn't own the stock

    std::cout << std::endl;
}

/* BROKEN!!!*/

TEST_CASE("Testing person's order related methods"){ 
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    // Person will buy stocks from the company
    auto person1 = std::make_shared<Person>(33, 100000, exchange, "person1", "123");

    // Apple creating stocks and placing a sell order
    auto apple = std::make_shared<Company>(11, 100, exchange, "Company1", "12345678");
    apple->createStock(1_ID, "AAPL"_SYM, 100_QTY);
    auto stockOpt = apple->getStock("AAPL");
    CHECK(stockOpt.has_value());
    auto stock = stockOpt.value();
    apple->placeOrder(stock, OrderType::SELL, 1, 100);

    // Person1 tries to buy these stocks. 
    person1->placeOrder(stock, OrderType::BUY, 1, 100);

    CHECK(person1->getBalance() == 100000 - 100);
    CHECK(person1->ownsStock("AAPL"));
    // Stock stock2 = person3.getStock("AAPL");

    // Person2 will be trying to buy those stocks, but wont match price
    auto person2 = std::make_shared<Person>(44, 100000, exchange, "person2", "123");
    // Person3 will be trying to sell those stocks and match price
    auto person3 = std::make_shared<Person>(55, 100000, exchange, "person3", "123");
    // Person3 tries to sell those stocks.
    CHECK(person1->ownsStock("AAPL"));
    stockOpt = person1->getStock("AAPL");
    CHECK(stockOpt.has_value());
    stock = stockOpt.value();
    person1->placeOrder(stock, OrderType::SELL, 1, 200);
    person2->placeOrder(stock, OrderType::BUY, 1, 150); // Doesn't match price
    person3->placeOrder(stock, OrderType::BUY, 1, 200); // Matches price = Stock will be transferred to person3
    
    CHECK_FALSE(person1->ownsStock("AAPL"));
    CHECK_FALSE(person2->ownsStock("AAPL"));
    
    CHECK(person3->ownsStock("AAPL"));
    CHECK(person1->getBalance() == (100000-100) + 200); // Person 1 has gained money from selling the stock
    CHECK(person2->getBalance() == 100000);
    CHECK(person3->getBalance() == 100000 - 200);

    // Person2 order is now in the orderbook
    // Person3 will sell the stock to person2
    person3->placeOrder(stock, OrderType::SELL, 1, 150); // This matches the price
    CHECK_FALSE(person3->ownsStock("AAPL"));
    
    CHECK(person2->ownsStock("AAPL"));
    CHECK(person3->getBalance() == (100000 - 200) + 150); // Person 3 has lost money from selling the stock
    CHECK(person2->getBalance() == 100000 - 150);

}


TEST_CASE("Init of person"){
    // Constructing two person1 and validating
    Person person1(1, 100, "Person1", "12345678");
    CHECK(person1.getBalance() == 100);
    person1.setBalance(200);
    CHECK(person1.getBalance() == 200);
}

TEST_CASE("adding stock as person (negative)") {
    Person person1(1, 100, "Person1", "12345678");
    Stock stock(1_ID, "AAPL"_SYM, 100_QTY);
    //person1.addStock(stock);
    CHECK_FALSE(person1.ownsStock("AAPL"));
}