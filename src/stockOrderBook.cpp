#include "stockOrderBook.hpp"
#include <algorithm>
#include <memory>

#include <iostream>

constexpr size_t default_bucket_count = 16;

typedef struct KeyValuePair KeyValuePair; // https://www.reddit.com/r/C_Programming/comments/19fbthf/how_do_i_hide_the_implementation_of_a_struct_in/

template<typename Key, typename Value>
using Container = std::vector<std::unique_ptr<KeyValuePair>>;

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
    [key](const std::unique_ptr<KeyValuePair>& kv) { return kv->value == key;});
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
        *it->value = value;
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

template<typename Key, typename Value>
requires ValidKey<Key>
void OrderBook<Key, Value>::openBook() const {
    for(int i = 0; i < table.size(); i++) {
        const Container& con = table[i];
        std::cout << "Bucket " << i << ": ";
        for (const auto kv : con) {
            std::cout << "{" << *kv->key << ", " << *kv->value << "}";
        }
        std::cout << "\n";
    }
}
