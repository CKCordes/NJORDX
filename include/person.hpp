#ifndef PERSON_H
#define PERSON_H

#include "trader.hpp"
#include <string>

class Person : public Trader {
private:
    std::string name;
    std::string cpr;

public:
    // Constructor
    Person(int id, const std::string& name, double initialBalance, const std::string& ssn);

    // Overridden methods
    void displayPortfolio() const override;
    Stock createStock(int stockID, const std::string& symbol, double initialPrice, Exchange& exchange) override;

    // Additional personal details accessors
    std::string getName() const;
    std::string getSSN() const;
};

#endif // PERSON_H
