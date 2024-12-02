#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "stockOrderBook.tpp"

// Test case for inserting
TEST_CASE("Inserting in orderbook") {
    OrderBook<int, float> orderBook;
    orderBook.insert(1, 1.0);
    orderBook.insert(2, 2.0);
    orderBook.insert(3, 3.0);
    CHECK(orderBook.contains(1) == true);
    CHECK(orderBook.contains(2) == true);
    CHECK(orderBook.contains(3) == true);
    CHECK(orderBook.contains(4) == false);
}

// Test case for erasing
TEST_CASE("Erasing in orderbook") {
    OrderBook<int, float> orderBook;
    orderBook.insert(1, 1.0);
    orderBook.insert(2, 2.0);
    orderBook.insert(3, 3.0);
    orderBook.erase(1);
    CHECK(orderBook.contains(1) == false);
    CHECK(orderBook.contains(2) == true);
    CHECK(orderBook.contains(3) == true);
    CHECK(orderBook.contains(4) == false);
}

// Test case for getting
TEST_CASE("Getting in orderbook") {
    OrderBook<int, float> orderBook;
    orderBook.insert(1, 1.0);
    orderBook.insert(2, 2.0);
    orderBook.insert(3, 3.0);
    CHECK(orderBook.get(1) == 1.0);
    CHECK(orderBook.get(2) == 2.0);
    CHECK(orderBook.get(3) == 3.0);
    CHECK_THROWS(orderBook.get(4));
}

// Testing iteration through the orderbook
TEST_CASE("Iterating through orderbook") {
    OrderBook<int, float> orderBook;
    orderBook.insert(1, 1.0);
    orderBook.insert(2, 2.0);
    orderBook.insert(3, 3.0);
    int count = 0;
    for (auto it = orderBook.begin(); it != orderBook.end(); ++it) {
        count++;
    }
    CHECK(count == 3);
}

// Testing the rule of 5
TEST_CASE("Testing rule of 5") {
    OrderBook<int, float> orderBook;
    orderBook.insert(1, 1.0);
    orderBook.insert(2, 2.0);
    orderBook.insert(3, 3.0);
    // Copy constructor
    OrderBook<int, float> orderBook2 = orderBook;
    CHECK(orderBook2.contains(1) == true);
    CHECK(orderBook2.contains(2) == true);
    CHECK(orderBook2.contains(3) == true);
    CHECK(orderBook2.contains(4) == false);
    // Copy assignment
    OrderBook<int, float> orderBook3;
    orderBook3 = orderBook;
    CHECK(orderBook3.contains(1) == true);
    CHECK(orderBook3.contains(2) == true);
    CHECK(orderBook3.contains(3) == true);
    CHECK(orderBook3.contains(4) == false);
    // Move constructor
    OrderBook<int, float> orderBook4 = std::move(orderBook);
    CHECK(orderBook4.contains(1) == true);
    CHECK(orderBook4.contains(2) == true);
    CHECK(orderBook4.contains(3) == true);
    CHECK(orderBook4.contains(4) == false);
    // Move assignment
    OrderBook<int, float> orderBook5;
    orderBook5 = std::move(orderBook2);
    CHECK(orderBook5.contains(1) == true);
    CHECK(orderBook5.contains(2) == true);
    CHECK(orderBook5.contains(3) == true);
    CHECK(orderBook5.contains(4) == false);
}

// Testcase for inserting many elements
TEST_CASE("Inserting many elements") {
    OrderBook<int, float> orderBook;
    for (int i = 0; i < 1000; i++) {
        orderBook.insert(i, i);
    }
    for (int i = 0; i < 1000; i++) {
    }
    CHECK(orderBook.contains(rand() % 1000) == true);
}