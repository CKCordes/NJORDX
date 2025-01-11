#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <concepts>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>
#include <optional>

class Stock;


/* Associative container for holding stocks and orders */
/* The idea is that stockID/orderID is the key */

// concept. Får en "a" ind. return type skal være noget der kan covnertes til size_t og bool
// fx. 0 og 1 kan converteres til bool
template<typename T>
concept ValidKey = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<size_t>; // First requirement for key to unordered_map
    { a == a } -> std::convertible_to<bool>; // Second requirement for key to unordered_map
}; 

// THIS MAP DOES NOT DYNAMICALLY RESIZE. IF PLANNING ON USING WITH HIGH LOADS: BE CAREFUL
// Valid key sørger for at en key opfylder kravene.
// kan ses lidt som om et if
template<ValidKey Key, typename Value>
class OrderBook {
    private:
        // Using a struct to hold the key and value so we can use move semantics
        // bruger et struct til at gemme strukturen af key valye pair
        struct KeyValuePair {
            Key key;
            Value value;
            // Constructor, flytter værdier ind
            // måske et problem vi bruger move
            KeyValuePair(Key k, Value v) : key(std::move(k)), value(std::move(v)) {}
        };

        // Our map is based on a vector.
        // A single container is a vector
        // namespace for ikke at skrive det hele hver gang (svarer til buckets)
        using Container = std::vector<std::shared_ptr<KeyValuePair>>;

        // To take care of hash collisions we create the table as a 2D table
        std::vector<Container> table;

        // For hashing the keys.
        std::hash<Key> hasher;

        // To find the correct key, in a single container.
        auto find_in_container(const Container&, const Key&) const;
        
        // To get the index for the "general" table. 
        size_t get_container_index(const Key&) const;

        static constexpr int initial_container_count = 17;

    public:
        // Custom iterator struct for our class
        struct Iterator { // inspiration from https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
            // det skal compileren bruge for at kunne lave en iterator
            // har vi ikke styr op
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = KeyValuePair;
            using pointer = KeyValuePair*;
            using reference = KeyValuePair&;

            // Her er hvad outer og inner iterator er
            using outer_iterator = typename std::vector<Container>::iterator;
            using inner_iterator = typename Container::iterator;

            // iterator constructor
            // outer svarer til table, inner svarer til containers
            Iterator(outer_iterator outer_it, outer_iterator outer_end)
            : outer_it(outer_it), outer_end(outer_end) {
                if (outer_it != outer_end) {
                    inner_it = outer_it->begin();
                    advance_to_next_valid();
                }
            }

            // reference til keyvaluepair
            reference operator*() const { return **inner_it; }

            // pointer til keyvaluepair
            pointer operator->() { return &**inner_it; }

            // operator overloading. pre-increment
            // referer til hjemmesiden
            Iterator& operator++() { 
                ++inner_it;
                advance_to_next_valid();
                return *this; 
            }

            // operator overloading. post-increment
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            // forstår ikke helt hvad der foregår i or statement
            bool operator==(const Iterator& other) const { 
                return outer_it == other.outer_it && (outer_it == outer_end || inner_it == other.inner_it); 
                }
            // bruger ovenstående operator
            bool operator!=(const Iterator& other) const { return !(*this == other); }

            private:
                outer_iterator outer_it;
                outer_iterator outer_end;
                inner_iterator inner_it;

                void advance_to_next_valid() {
                    // Hvis vi ikke er nået til enden af outer og inner er i enden af container, så kører vi
                    while (outer_it != outer_end && inner_it == outer_it->end()) {
                        ++outer_it;
                        if (outer_it != outer_end) {
                            inner_it = outer_it->begin();
                        }
                    }
                }
        }; 
        // Implementing the rule of 5
        // bruger rule of 5(3), da vi har vores egen destructor
        // Constructor
        OrderBook(int bucket_count = initial_container_count);
        // Destructor 1
        ~OrderBook();
        // Copy constructor 2
        OrderBook(const OrderBook& other);
        // Copy Assignment 3
        OrderBook& operator=(const OrderBook& other);
        // Move constructor 4
        // double & er en reference til en r-value, som er en midlertidig værdi
        OrderBook(OrderBook&& other) noexcept;
        // Move Assignment 5
        OrderBook& operator=(OrderBook&& other) noexcept;
        

         // Enable this method only if Key is of type Stock
        template<typename V = Value>
        // bruger enable_if til kun at enable metoden, hvis value er en stock (trader)
        // giver metoden retyrn type "value", som er en stock
        typename std::enable_if<std::is_same<V, std::shared_ptr<Stock>>::value>::type
        insertStock(const Key& key, const Value& value) noexcept;

        void insert(const Key& key, const Value& value) noexcept;
        void erase(const Key& key);
        bool contains(const Key& key) const;
        std::optional<Value> get(const Key& key) const;

        Iterator begin() { return Iterator(table.begin(), table.end()); }
        Iterator end() { return Iterator(table.end(), table.end()); }      
};
// Constructor
template<typename Key, typename Value>
requires ValidKey<Key> // requires sørger for at keyen overholder requirements
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
        // !
        const Container& other_con = other.table[i];
        Container& this_con = table[i];

        for(const auto& kv : other_con) {
            // unique legacy
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
    // strong guarentee
    OrderBook<Key, Value> tmp(other);
    std::swap(*this, tmp);
    return *this;
}

// Move constructor
template<typename Key, typename Value>
requires ValidKey<Key>
// må være noexcept, fordi move er noexcept hvis strukturen den bruges er i orden
OrderBook<Key, Value>::OrderBook(OrderBook&& other) noexcept : table(std::move(other.table)) {}

// Move assignment
template<typename Key, typename Value>
requires ValidKey<Key>
// skriver noexcept fordi det er move
OrderBook<Key, Value>& OrderBook<Key, Value>::operator=(OrderBook&& other) noexcept {
    // strong guarentee
    if (this == &other) {
        return *this;
    }
    table = std::move(other.table);
    return *this;
}

// returns an iterator to the first element found in container. If it is not there it returns the end of the container
template<typename Key, typename Value>
requires ValidKey<Key>
auto OrderBook<Key, Value>::find_in_container(const Container& con, const Key& key) const {
    // Explanation: Find_if takes the range of elements to examine
    // The third parameter is the value to compare the elements to. This is the lambda expression
    // [] captures the key that we are given in the function. 
    // () takes the kv that are in the vector
    // {} is where we compare the keys
    return std::find_if(con.begin(), con.end(),
    [key](const std::shared_ptr<KeyValuePair>& kv) { return kv->key == key;});
}

template<typename Key, typename Value>
requires ValidKey<Key>
size_t OrderBook<Key, Value>::get_container_index(const Key& key) const {
    return OrderBook::hasher(key) % table.size();
}

template<typename Key, typename Value>
requires ValidKey<Key>
template<typename V>
typename std::enable_if<std::is_same<V, std::shared_ptr<Stock>>::value, void>::type
OrderBook<Key, Value>::insertStock(const Key& key, const Value& value) noexcept {
    size_t table_index = get_container_index(key);
    Container& con = table[table_index];
    auto it = find_in_container(con, key);
    if (it != con.end()) {
        // The key exists, it means that the stock is already in the container, so we should update the number of stocks in the container
        (*it)->value->addStocks(value->getNumberOfStocks());
    } else {
        // We need to make the pair and insert it in the container
        /* Strong guarentee */
        Container tmp(con);
        tmp.push_back(std::make_unique<KeyValuePair>(key, value)); // unique er legacy
        con.swap(tmp);
    }
}

template<typename Key, typename Value>
requires ValidKey<Key>
void OrderBook<Key, Value>::insert(const Key& key, const Value& value) noexcept {
    size_t table_index = get_container_index(key);
    Container& con = table[table_index];
    auto it = find_in_container(con, key);
    if (it != con.end()) {
        // The key exists, update value. The iterator is a pointer to keyvalpair
        (*it)->value = value;
    } else {
        // We need to make the pair and insert it in the container
        /* Strong guarentee */
        Container tmp(con);
        tmp.push_back(std::make_unique<KeyValuePair>(key, value));
        con.swap(tmp);
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
        std::cout << "Key not found" << std::endl;
    }
}

template<typename Key, typename Value>
requires ValidKey<Key>
bool OrderBook<Key, Value>::contains(const Key& key) const {
    size_t table_index = get_container_index(key);
    const Container& con = table[table_index];
    return find_in_container(con, key) != con.end();
}

template<typename Key, typename Value>
requires ValidKey<Key>
// std::optional retunere en nullopt, hvis værdien ikke eksisterer
// ellers returnere den optinal "value"
std::optional<Value> OrderBook<Key, Value>::get(const Key& key) const {
    size_t table_index = get_container_index(key);
    const Container& con = table[table_index];
    auto it = find_in_container(con, key);
    if(it != con.end()) {
        return (*it)->value;
    } else {
        std::cout << "Key not found" << std::endl;
        return std::nullopt;
    }
}

#endif // ORDERBOOK_H