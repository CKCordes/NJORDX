#ifndef COMPANY_H
#define COMPANY_H

#include "trader.hpp"
#include <string>

class Company : public Trader {
private:
    std::string companyName;
    std::string cvr;

public:
    // Constructor
    Company(int id, const std::string& name, double initialBalance, const std::string& regNumber);

    // Overridden methods
    void displayPortfolio() const override;
    Stock createStock(int stockID, const std::string& symbol, double initialPrice, Exchange& exchange) override;

    // Additional company details accessors
    std::string getCompanyName() const;
    std::string getRegistrationNumber() const;
};

#endif // COMPANY_H
