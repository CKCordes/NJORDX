#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <unordered_map>
#include <concepts>

#include "order.hpp"
#include "stock.hpp"

/* Associative container for holding stocks and orders */
/* The idea is that stockID/orderID is the key */

template<typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<size_t>;
}; // First requirement for key to unordered_map

template<typename T>
concept EqComparable = requires(T a) {
    { a == a } -> std::convertible_to<bool>;
}; // Second requirement for key to unordered_map

template<typename K>
concept ValidKey = Hashable<K> && EqComparable<K>;

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

        // Self explainatory
        static const size_t default_bucket_count = 16

        // to find the correct key, in a single container.
        auto find_in_container(const Container&, const Key&) const;
        
        // The to get the index for the "general" table. 
        size_t get_container_index(const Key&) const;

    public:
        OrderBook(int);
        void insert(const Key&, const Value&);
        void erase(const Key&);
        bool contains(const Key&) const;
        Value get(const Key&) const;
        void openBook() const;
};

#endif