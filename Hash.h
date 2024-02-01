#ifndef DS_PROJECT_HASH_H
#define DS_PROJECT_HASH_H
#include "kdtree.h"
#include "vectorT.h"
#include "linkedlistT.h"


template<class T>
class Hash {
private:
    Vector<Linkedlist<T>> values;
    int hash_table_size;
    int multiple_hashing(int key,double coef = 0.6180339887);
public:
    Hash();
    void insert(int key,T value);
    T* search(int key);

};


#endif //DS_PROJECT_HASH_H
