#ifndef Company_H
#define Company_H

#include "trader.tpp"

class Company : public Trader<Company>{
public:
    Company(int id, double initialBalance, Njordx* exchange) 
    : Trader(id, initialBalance, exchange) {}
    ~Company() {}

    
};

#endif // Company_H