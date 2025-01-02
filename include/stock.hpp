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
    void addStocks(int amount) noexcept;
    void removeStocks(int amount);

    // Display stock information
    void displayInfo() const;

    // Overloaded equality operator
    bool operator==(const Stock& other) const;
};

// User defined literals
namespace StockLiterals {
    int operator"" _ID(unsigned long long id) {
        return static_cast<int>(id);
    }
    std::string operator"" _SYM(const char* symbol, std::size_t) {
        return std::string(symbol);
    }
    int operator"" _QTY(unsigned long long qty) {
        return static_cast<int>(qty);
    }
}
using namespace StockLiterals;



#endif // STOCK_H
