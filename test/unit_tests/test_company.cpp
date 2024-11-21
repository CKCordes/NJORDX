#include "doctest.h"
#include "company.tpp"
#include "njordx.hpp"

TEST_CASE("Testing company class"){


    Company company1(1, 100, "Company1", "12345678");
    Company company2(2, 200, nullptr, "Company2", "87654321");

    CHECK(company1.getBalance() == 100); 
    company1.setBalance(200);
    CHECK(company1.getBalance() == 200);  
}