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
    Person(int id, double initialBalance, const std::string& name, const std::string& ssn)
        : Trader<Person>(id, initialBalance), name(name), cpr(ssn) {}
    Person() : Trader<Person>(0, 0.0), name(""), cpr("") {} // Default constructor

    // Overridden methods
    void printTrader() const {
        std::cout << "Trader ID: " << traderID << std::endl;
    }
    void displayPortfolio() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "CPR: " << cpr << std::endl;
        printTrader(); 
        std::cout << "Balance: " << balance << std::endl;
        // Should print owned stocks
        std::cout << "Owned stocks: " << std::endl;
    
        for (auto& stock : ownedStocks) {
            std::cout << "Stock: " << stock.key << ", Amount: " << stock.value.get()->getNumberOfStocks() << std::endl;
        }

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
