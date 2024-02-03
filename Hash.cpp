#include "Hash.h"
#include <cmath>

template<class T>
Hash<T>::Hash() : values(Vector<Linkedlist<T>>(100)) , hash_table_size(100) {}

template<>
Hash<PizzaShop>::Hash() : values(Vector<Linkedlist<PizzaShop>>(100)), hash_table_size(100) {}

template<>
Hash<Vector<node_t<KDTree>>>::Hash() : values(Vector<Linkedlist<Vector<node_t<KDTree>>>>(100)), hash_table_size(100) {}

template <class T>
int Hash<T>::multiple_hashing(int key, double coef) {
    double product = key * coef;
    double frac_part = product - floor(product);
    return static_cast<long long int>(frac_part * hash_table_size);
}

template<>
size_t Hash<PizzaShop>::hash_string(const std::string &str) {
    size_t hash = 5381;
    for(char ch : str) {
        hash = (hash * 33) ^ static_cast<unsigned char>(ch);
    }
    return hash;
}

template <class T>
void Hash<T>::insert(int key,T value) {
    int index = this->multiple_hashing(key);
    this->values[index].push_back(key,value);
}

template<>
void Hash<PizzaShop>::insert(PizzaShop value) {
    size_t key = this->hash_string(value.getMainBranchName());
    int index = key % this->hash_table_size;
    this->values[index].push_back(key,value);
}

template<>
void Hash<Vector<node_t<KDTree>>>::insert(int key, Vector<node_t<KDTree>> value) {
    int index = this->multiple_hashing(key);
    this->values[index].push_back(key,value);
}

template <class T>
T* Hash<T>::search(int key) {
    int index = this->multiple_hashing(key);
    return this->values[index].search(key);
}


template<>
PizzaShop Hash<PizzaShop>::search(PizzaShop key) {
    int _key = this->hash_string(key.getMainBranchName());
    int index = _key % this->hash_table_size;
    return this->values[index].search(_key)->get_value();
}

template<>
PizzaShop Hash<PizzaShop>::search(std::string key) {
    int _key = this->hash_string(key);
    int index = _key % this->hash_table_size;
    return this->values[index].search(_key)->get_value();
}

template<>
Linkedlist<PizzaShop> Hash<PizzaShop>::searchForList(string key) {
    int _key = this->hash_string(key);
    int index = _key % this->hash_table_size;
    return this->values[index];
}


template<>
Vector<node_t<KDTree>> Hash<Vector<node_t<KDTree>>>::search1(int key) {
    int index = this->multiple_hashing(key);
    return this->values[index].search(key)->get_value();
}