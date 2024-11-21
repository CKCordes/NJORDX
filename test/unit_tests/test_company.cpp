#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"

TEST_CASE("Testing company class"){


    Company company1(1, 100, nullptr, "Company1", "12345678");
    CHECK(company1.getBalance() == 100); 
    company1.setBalance(200);
    CHECK(company1.getBalance() == 200);  
}