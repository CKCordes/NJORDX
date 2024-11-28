#ifndef Company_H
#define Company_H

#include "trader.tpp"

class Company : public Trader<Company>{
    std::string companyName;
    std::string cvr;

public:
    Company(int id, double initialBalance, Njordx* exchange, const std::string& name, const std::string& regNumber) 
    :  Trader<Company>(id, initialBalance, exchange), companyName(name), cvr(regNumber)  {}
    Company(int id, double initialBalance, const std::string& name, const std::string& regNumber)
    : Trader<Company>(id, initialBalance), companyName(name), cvr(regNumber) {}
    ~Company() {}

    // Overridden methods
    void printTrader() const {
        std::cout << "Trader ID: " << traderID << std::endl;
    }
    void displayPortfolio() const {
        std::cout << "Company Name: " << companyName << std::endl;
        std::cout << "CVR: " << cvr << std::endl;
        printTrader();
        std::cout << "Balance: " << balance << std::endl;
        std::cout << "Exchange: " << exchange << std::endl;
    }

    void createStock(int stockID, const std::string& symbol, int numberOfStocks) {
        Stock newStock(stockID, symbol, numberOfStocks);
        ownedStocks.insert(symbol, newStock);
    }

    // Additional company details accessors
    std::string getCompanyName() const {
        return companyName;
    }
    std::string getRegistrationNumber() const {
        return cvr;
    }

    
};

#endif // Company_H