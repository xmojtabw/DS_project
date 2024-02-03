#ifndef _LINKEDLISTT_H_
#define _LINKEDLISTT_H_
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

public:
    node_t() = default;
    node_t(int _key, node_t* _next,T value);
    int get_key() const;
    T get_value() const;
    node_t<T>* get_next() const;

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
    node_t<T>* search(int _key,T val);
    node_t<T>* pop_anywhere(int _key);
    node_t<T>* get_first() const;
};

template<>
class Linkedlist<KDTree> {
private:
    node_t<KDTree>* first, *last;
    int size;
public:
    Linkedlist() = default;
    Linkedlist(const Linkedlist<KDTree> &other);
    Linkedlist(node_t<KDTree>* _first);
    void push_back(int key, KDTree value);
    node_t<KDTree>* get_first() const;
};




#endif //DS_PROJECT_LINKEDLISTT_H
