#ifndef _HASH_H_
#define _HASH_H_
#include "vectorT.h"
#include "linkedlistT.h"


template<class T>
class Hash {
private:
    Vector<Linkedlist<T>> values;
    int hash_table_size;
    int multiple_hashing(int key,double coef = 0.6180339887);
public:
    size_t hash_string(const std::string& str);
    Hash();
    void insert(int key, T value);
    void insert(T value);
    void add(int key,int subkey,T value);
    T* search(int key);
    T search(T key);
    T search(std::string key);
    T search1(int key);
    Linkedlist<T> searchForList(string key);
};


#endif //DS_PROJECT_HASH_H
