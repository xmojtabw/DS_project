#include "Hash.h"
#include <cmath>

template<class T>
Hash<T>::Hash() : values(Vector<T>(100)) , hash_table_size(100) {}


template <class T>
int Hash<T>::multiple_hashing(int key, double coef) {
    double product = key * coef;
    double frac_part = product - floor(product);
    return static_cast<long long int>(frac_part * hash_table_size);
}

template <class T>
void Hash<T>::insert(int key,T value) {
    int index = this->multiple_hashing(key);
    this->values[index].push_back(key,value);
}

template <class T>
T* Hash<T>::search(int key) {
    int index = this->multiple_hashing(key);
    return this->values[index].search(key);
}
