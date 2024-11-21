#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {
private:
    int stockID;
    std::string symbol;
    int numberOfStocks;

public:
    // Constructor
    Stock(int id, const std::string& symbol, int numberOfStocks);

    // Getters and setters
    int getStockID() const;
    std::string getSymbol() const;
    int getNumberOfStocks() const;
    void addStocks(int amount);
    bool removeStocks(int amount);

    // Display stock information
    void displayInfo() const;

    // Overloaded equality operator
    bool operator==(const Stock& other) const;
};



#endif // STOCK_H
