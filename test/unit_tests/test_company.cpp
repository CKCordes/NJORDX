#include "doctest.h"
#include "company.tpp"

TEST_CASE("Testing company class"){

    Company company(1, 100, nullptr);
    CHECK(company.getBalance() == 100); 
    company.setBalance(200);
    CHECK(company.getBalance() == 200);  
}