#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {
private:
    int stockID;
    std::string symbol;
    double price;

public:
    // Constructor
    Stock(int id, const std::string& symbol, double initialPrice);

    // Getters and setters
    int getStockID() const;
    std::string getSymbol() const;
    double getPrice() const;
    void setPrice(double newPrice);

    // Display stock information
    void displayInfo() const;
};

#endif // STOCK_H
