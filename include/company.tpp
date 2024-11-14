#ifndef Company_H
#define Company_H

#include "trader.tpp"

class Company : public Trader<Company>{
    std::string companyName;
    std::string cvr;

public:
    Company(int id, double initialBalance, Njordx* exchange, const std::string& name, const std::string& regNumber) 
    :  traderID(id), balance(initialBalance), exchange(exchange), companyName(name), cvr(regNumber)  {}
    ~Company() {}

    // displayPortfolio() const {
        
    // }

    
};

#endif // Company_H