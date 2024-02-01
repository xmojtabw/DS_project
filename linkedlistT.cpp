#include "linkedlistT.h"

template <class T>
node_t<T>::node_t(int _key, node_t *_next, T value) {
    this->key = _key;
    this->next = _next;
    this->value = value;
}

template<>
node_t<KDTree>::node_t(int _key, node_t<KDTree> *_next, KDTree value) {
    this->key = _key;
    this->next = _next;
    this->value = KDTree(value);
}

template <class T>
Linkedlist<T>::Linkedlist() : first(nullptr), last(nullptr), size(0) {}

template <class T>
Linkedlist<T>::Linkedlist(node_t<T> *_first) {
    node_t<T>* tmp = _first;
    this->first = _first;
    this->last = _first;
    this->size = 0;
    while(tmp->next != nullptr) {
        this->last = tmp->next;
        tmp = tmp->next;
        size++;
    }
    this->last->next = nullptr;
}

template<class T>
Linkedlist<T>::Linkedlist(const Linkedlist<T> &other) {
    node_t<T>* itr = other.first;
    node_t<T>* this_first = new node_t<T>(other.first->key, nullptr,other.first->value);
    node_t<T>* tmp = this_first;
    while(itr->next) {
        itr = itr->next;
        tmp->next = new node_t<T>(itr->key, nullptr,itr->value);
        tmp = tmp->next;
    }
    this->first = this_first;
    this->last = tmp;
    this->size = other.size;
}

template <class T>
void Linkedlist<T>::push_back(int key,T value) {
    node_t<T>* new_node = new node_t<T>(key,nullptr,value);
    if(this->first == nullptr) {
        this->first = new_node;
        this->first->next = nullptr;
    }
    else {
        this->last->next = new_node;
    }
    this->last = new_node;
    this->size++;
}

template<class T>
node_t<T>* Linkedlist<T>::search(int _key) {
    node_t<T>* tmp = this->first;
    while(tmp) {
        if(tmp->key == _key)
            break;
        tmp = tmp->next;
    }
    return tmp;
}

template<class T>
node_t<T>* Linkedlist<T>::pop_anywhere(int _key) {
    node_t<T>* tmp = this->first;
    node_t<T>* result = nullptr;
    while(tmp) {
        if(tmp->next->key == _key) {
            result = tmp->next;
            tmp->next = tmp->next->next;
        }
    }
    return result;
}

