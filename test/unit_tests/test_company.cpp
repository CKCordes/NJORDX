#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"

TEST_CASE("Testing company class"){

    Njordx* exchange();

    Company company1(1, 100, exchange);
    CHECK(company1.getBalance() == 100); 
    company1.setBalance(200);
    CHECK(company1.getBalance() == 200);  
}