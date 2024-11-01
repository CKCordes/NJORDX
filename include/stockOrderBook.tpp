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

        static constexpr int initial_bucket_count = 16;

    public:
        // Implementing the rule of 5
        // Constructor
        OrderBook(int bucket_count = initial_bucket_count);
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
};
// Constructor
template<typename Key, typename Value>
requires ValidKey<Key>
OrderBook<Key, Value>::OrderBook(int bucket_count) : table(bucket_count) {}

// Destructor
template<typename Key, typename Value>
requires ValidKey<Key>
OrderBook<Key, Value>::~OrderBook() {
    for(auto& con : table) {
        con.clear();
    }
}

// Copy constructor
template<typename Key, typename Value>
requires ValidKey<Key>
OrderBook<Key, Value>::OrderBook(const OrderBook& other) : table(other.table.size()) {
    for(size_t i = 0; i < other.table.size(); i++) {
        const Container& other_con = other.table[i];
        Container& this_con = table[i];

        for(const auto& kv : other_con) {
            this_con.push_back(std::make_unique<KeyValuePair>(*kv));
        }
    }
}

// Copy Assignment
template<typename Key, typename Value>
requires ValidKey<Key>
OrderBook<Key, Value>& OrderBook<Key, Value>::operator=(const OrderBook& other) {
    if (this == &other) {
        return *this;
    }
    OrderBook<Key, Value> tmp(other);
    std::swap(*this, tmp); // Virker det her virkelig?
    return *this;
}

// Move constructor
template<typename Key, typename Value>
requires ValidKey<Key>
OrderBook<Key, Value>::OrderBook(OrderBook&& other) noexcept : table(std::move(other.table)) {}

// Move assignment
template<typename Key, typename Value>
requires ValidKey<Key>
OrderBook<Key, Value>& OrderBook<Key, Value>::operator=(OrderBook&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    table = std::move(other.table);
    return *this;
}

template<typename Key, typename Value>
requires ValidKey<Key>
auto OrderBook<Key, Value>::find_in_container(const Container& con, const Key& key) const {
    // To explain this abomination. Find_if takes the range of elements to examine
    // The third parameter is the value to compare the elements to. This is the lambda expression
    // [] captures the key that we are given in the function. 
    // () takes the kv that are in the vector
    // {} is where we compare the keys
    return std::find_if(con.begin(), con.end(),
    [key](const std::unique_ptr<KeyValuePair>& kv) { return kv->key == key;});
}

template<typename Key, typename Value>
requires ValidKey<Key>
size_t OrderBook<Key, Value>::get_container_index(const Key& key) const {
    return OrderBook::hasher(key) % table.size();
}

template<typename Key, typename Value>
requires ValidKey<Key>
void OrderBook<Key, Value>::insert(const Key& key, const Value& value) {
    size_t table_index = get_container_index(key);
    Container& con = table[table_index];
    auto it = find_in_container(con, key);
    if (it != con.end()) {
        // The key exists, update value. The iterator is a pointer to keyvalpair
        (*it)->value = value;
    } else {
        // We need to make the pair and insert it in the container
        con.push_back(std::make_unique<KeyValuePair>(key, value));
    }
}

template<typename Key, typename Value>
requires ValidKey<Key>
void OrderBook<Key, Value>::erase(const Key& key) {
    size_t table_index = get_container_index(key);
    Container& con = table[table_index];
    auto it = find_in_container(con, key);
    if(it != con.end()) {
        con.erase(it);
    } else {
        throw std::out_of_range("Key not found"); // shouldnt be exception
    }
}

template<typename Key, typename Value>
requires ValidKey<Key>
bool OrderBook<Key, Value>::contains(const Key& key) const {
    size_t table_index = get_container_index(key);
    Container& con = table[table_index];
    return find_in_container(con, key) != con.end();
}

template<typename Key, typename Value>
requires ValidKey<Key>
Value OrderBook<Key, Value>::get(const Key& key) const {
    size_t table_index = get_container_index(key);
    Container& con = table[table_index];
    auto it = find_in_container(con, key);
    if(it != con.end()) {
        return *it->value;
    } else {
        throw std::out_of_range("Key not found"); // shouldnt be exception
    }
}


#endif // ORDERBOOK_H