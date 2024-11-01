#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <unordered_map>
#include <concepts>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>


/* Associative container for holding stocks and orders */
/* The idea is that stockID/orderID is the key */

template<typename T>
concept ValidKey = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<size_t>; // First requirement for key to unordered_map
    { a == a } -> std::convertible_to<bool>; // Second requirement for key to unordered_map
}; 

// THIS MAP DOES NOT DYNAMICALLY RESIZE. IF PLANNING ON USING WITH HIGH LOADS: BE CAREFUL
template<ValidKey Key, typename Value>
class OrderBook {
    private:
        struct KeyValuePair {
            Key key;
            Value value;

            KeyValuePair(Key k, Value v) : key(std::move(k)), value(std::move(v)) {}
        };

        // Our map is based on a vector.
        // A single container is a vector
        using Container = std::vector<std::unique_ptr<KeyValuePair>>;

        // To take care of hash collisions we create the table as a 2D table
        std::vector<Container> table;

        // For hashing the keys.
        std::hash<Key> hasher;

        // to find the correct key, in a single container.
        auto find_in_container(const Container&, const Key&) const;
        
        // The to get the index for the "general" table. 
        size_t get_container_index(const Key&) const;

    public:
        // Implementing the rule of 5
        // Constructor
        OrderBook(int bucket_count);
        // Destructor 1
        ~OrderBook();
        // Copy constructor 2
        OrderBook(const OrderBook& other);
        // Copy Assignment 3
        OrderBook& operator=(const OrderBook& other);
        // Move constructor 4
        OrderBook(OrderBook&& other) noexcept;
        // Move Assignment 5
        OrderBook& operator=(OrderBook&& other) noexcept;
        

        void insert(const Key& key, const Value& value);
        void erase(const Key& key);
        bool contains(const Key& key) const;
        Value get(const Key& key) const;
        void openBook() const;
};

#endif // ORDERBOOK_H