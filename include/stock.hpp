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
// Kan være med til at give udvikleren bedre readability, 
// bruges til casting
// bruger constexpr for at det lavet i compile time
namespace StockLiterals {
    constexpr int operator"" _ID(unsigned long long id) {
        return static_cast<int>(id);
    }
    constexpr std::string operator"" _SYM(const char* symbol, std::size_t) {
        return std::string(symbol);
    }
    constexpr int operator"" _QTY(unsigned long long qty) {
        return static_cast<int>(qty);
    }
}
using namespace StockLiterals;
// bruger namespace hernede for at undgå at skulle skrive det hver gang andre steder
// måske ulovligt, da man ikke ved hvor det kommer fra


#endif // STOCK_H
