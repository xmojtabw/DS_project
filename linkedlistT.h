#ifndef DS_PROJECT_LINKEDLISTT_H
#define DS_PROJECT_LINKEDLISTT_H
#include "kdtree.h"

template <class T>
class Linkedlist;

template <class T>
class node_t {
    friend class Linkedlist<T>;
private:
    T value;
    int key;
    node_t* next;
    node_t() = default;
    node_t(int _key, node_t* _next,T value);

};


template <class T>
class Linkedlist {
private:
    node_t<T>* first, *last;
    int size;
public:
    Linkedlist();
    Linkedlist(node_t<T>* first);
    Linkedlist(const Linkedlist<T> &other);
    void push_back(int key,T value);
    node_t<T>* search(int _key);
    node_t<T>* pop_anywhere(int _key);
};

#endif //DS_PROJECT_LINKEDLISTT_H
