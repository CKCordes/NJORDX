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