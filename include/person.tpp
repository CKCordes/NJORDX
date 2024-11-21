#ifndef PERSON_H
#define PERSON_H

#include "trader.tpp"
#include <string>

class Person : public Trader<Person> {
private:
    std::string name;
    std::string cpr;

public:
    // Constructor
    Person(int id, double initialBalance, Njordx* exchange, const std::string& name, const std::string& ssn)
        : Trader<Person>(id, initialBalance, exchange), name(name), cpr(ssn) {}

    // Overridden methods
    void displayPortfolio() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "CPR: " << cpr << std::endl;
        std::cout << "Trader ID: " << traderID << std::endl;
        std::cout << "Balance: " << balance << std::endl;
        std::cout << "Exchange: " << exchange << std::endl;
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
