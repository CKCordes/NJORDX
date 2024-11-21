#ifndef PERSON_H
#define PERSON_H

#include "trader.tpp"
#include <string>

class Person : public Trader {
private:
    std::string name;
    std::string cpr;

public:
    // Constructor
    Person(int id, const std::string& name, double initialBalance, const std::string& ssn)
        : traderID(id), name(name), balance(initialBalance), cpr(ssn) {}

    // Overridden methods
    void displayPortfolio() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "CPR: " << cpr << std::endl;
        std::cout << "Trader ID: " << traderID << std::endl;
        std::cout << "Balance: " << balance << std::endl;
        // std::cout << "Exchange: " << exchange << vstd::endl;
    }


    // Additional personal details accessors
    std::string getName() const {
        return name;
    }
    std::string getSSN() const {
        return cpr;
    }
};

#endif // PERSON_H
