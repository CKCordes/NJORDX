#include "doctest.h"
#include "person.tpp"
#include "company.tpp"
#include "njordx.hpp"

TEST_CASE("Testing initialization of person class and getters and setters"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();


    Person person1(1, 100, exchange, "Person1", "12345");
    CHECK(person1.getBalance() == 100); 
    person1.setBalance(200);
    CHECK(person1.getBalance() == 200);  
    CHECK(person1.getTraderID() == 1);
    CHECK(person1.getName() == "Person1");
    CHECK(person1.getSSN() == "12345");

    // Stock google = Stock(1, "GOOGL", 100);
    // person1.addStock(google);
    // CHECK(person1.getStock("GOOGL") == google);
    // person1.removeStock(google);
    // CHECK_THROWS(person1.getStock("GOOGL") == google);
}

TEST_CASE("Testing delegating person constructors, joinExchange() and displayPortfolio()"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();
      
    Person person2(2, 300, "Person2", "6789");
    CHECK(person2.getBalance() == 300);
    person2.joinExchange(exchange);

    person2.displayPortfolio();
}

TEST_CASE("Testing person's order related methods"){
    // Constructing a new exchange
    Njordx* exchange = new Njordx();

    Person person3(3, 100000, exchange, "person3", "123");

    // Apple creating stocks and placing a sell order
    Company apple(1, 100, exchange, "Company1", "12345678");
    apple.createStock(1, "AAPL", 100);
    Stock stock = apple.getStock("AAPL");
    apple.placeOrder(stock, OrderType::SELL, 1, 100);

    std::cout << person3.getBalance() << std::endl;
    // Person3 tries to buy those stocks. 
    CHECK(person3.placeOrder(stock, OrderType::BUY, 1, 100));
    std::cout << person3.getBalance() << std::endl;

    // Person4 will be trying to buy those stocks
    Person person4(4, 100000, exchange, "person4", "123");

    // Person3 tries to sell those stocks.
    CHECK(person3.placeOrder(stock, OrderType::SELL, 1, 100));
    CHECK(person4.placeOrder(stock, OrderType::BUY, 1, 100));

    // Stock apple = Stock(1, "AAPL", 100);
    // Stock google = Stock(2, "GOOGL", 200);
    // person3.addStock(apple);
    // person3.addStock(google);

    // CHECK(person3.placeOrder(google, OrderType::BUY, 1, 100)); // ? der bliver printet at google ikke er på markedet, men den retunere stadig true. Er det rigtigt?
    // CHECK(person3.placeOrder(apple,OrderType::SELL, 1, 100));

    // Order buyorder(OrderType::BUY, 3, std::make_shared<Stock>(google), 100, 50.0);    
    // Order sellorder(OrderType::SELL, 3, std::make_shared<Stock>(google), 100, 50.0);

    // CHECK(person3.getBalance() == 100000);
    // person3.handleOrder(sellorder);
    // CHECK(person3.getBalance() == 100000 + (100 * 50.0));
    // person3.handleOrder(buyorder);
    // CHECK(person3.getBalance() == 100000);
}
#include "doctest.h"
#include "person.tpp"
#include "njordx.hpp"

TEST_CASE("Init of person"){
    // Constructing two company1 and validating
    Person person1(1, 100, "Person1", "12345678");
    CHECK(person1.getBalance() == 100);
    person1.setBalance(200);
    CHECK(person1.getBalance() == 200);
}

TEST_CASE("adding stock as person (negative)") {
    Person person1(1, 100, "Person1", "12345678");
    Stock stock(1, "AAPL", 100);
    //person1.addStock(stock);
    CHECK_FALSE(person1.ownedStocks.contains("AAPL"));
}