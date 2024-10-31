#include <stockOrderBook.hpp>

OrderBook::OrderBook(size_t bucket_count = default_bucket_count) : table(bucket_count) {}

auto OrderBook::find_in_container(const Container& con, const Key& key) const {
    // To explain this abomination. Find_if takes the range of elements to examine
    // The third parameter is the value to compare the elements to. This is the lambda expression
    // [] captures the key that we are given in the function. 
    // () takes the kv that are in the vector
    // {} is where we compare the keys
    return std::find_if(con.begin(), con.end(),
    [key&](const std::unique_ptr<KeyValuePair>& kv) { return kv->value == key;});
}

size_t OrderBook::get_container_index(const Key& key) const {
    return hasher(key) % table.size();
}

template<ValidKey K, typename V>
void OrderBook::insert(const K key, const V value) {
    size_t table_index = get_container_index(key);
    Container& con = table[index];
    auto it = find_in_container(con, key);
    if (it != con.end()) {
        // The key exists, update value. The iterator is a pointer to keyvalpair
        (*it)->value = value
    } else {
        // We need to make the pair and insert it in the container
        con.push_back(std::make_unique<KeyValuePair>(key, value))
    }
}

template<ValidKey K, typename V>
void OrderBook::erase(const K key) {
    size_t table_index = get_container_index(key);
    Container& con = table[index];
    auto it = find_in_container(con, key);
    if(it != con.end()) {
        con.erase(it)
    } else {
        throw std::out_of_range("Key not found")
    }
}

template<ValidKey K, typename V>
bool OrderBook::contains(const K key) const {
    size_t table_index = get_container_index(key);
    Container& con = table[index];
    return find_in_container(con, key) != con.end();
}

template<ValidKey K, typename V>
V OrderBook::get(const K key) const {
    size_t table_index = get_container_index(key);
    Container& con = table[index];
    auto it = find_in_container(con, key);
    if(it != con.end()) {
        return (it*)->value;
    } else {
        throw std::out_of_range("Key not found")
    }
}

template<ValidKey K, typename V>
void OrderBook::openBook() const {
    for(int i = 0; i < table.size(); i++) {
        const Container& con = table[i]
        std::cout << "Bucket " << i << ": ";
        for (const auto kv : con) {
            std::cout << "{" << (kv*)->key << ", " << (kv*)->value << "}";
        }
        std::cout << "\n";
    }
}
