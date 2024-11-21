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

    displayPortfolio() const {
        std::cout << "Company Name: " << companyName << std::endl;
        std::cout << "CVR: " << cvr << std::endl;
        std::cout << "Trader ID: " << traderID << std::endl;
        std::cout << "Balance: " << balance << std::endl;
        std::cout << "Exchange: " << exchange << std::endl;
    }

    Stock createStock(int stockID, const std::string& symbol, double initialPrice, Exchange& exchange){
        
    }

    // Additional company details accessors
    std::string getCompanyName() const;
    std::string getRegistrationNumber() const;

    
};

#endif // Company_H