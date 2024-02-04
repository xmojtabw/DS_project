#include "linkedlistT.h"
#include "neighberhood.h"

template <class T>
node_t<T>::node_t(int _key, node_t *_next, T value) {
    this->key = _key;
    this->next = _next;
    this->value = value;
}

template<>
node_t<Vector<node_t<Vector<PizzaShop>>>>::node_t(int _key, node_t<Vector<node_t<Vector<PizzaShop>>>> *_next, Vector<node_t<Vector<PizzaShop>>> _value) {
    this->key = _key;
    this->value = _value;
    this->next = _next;

}
template<>
node_t<Vector<PizzaShop>>::node_t(int _key, node_t<Vector<PizzaShop>> *_next, Vector<PizzaShop> value) {
    this->key = _key;
    this->next = _next;
    this->value = Vector<PizzaShop>(value);
}

template<class T>
int node_t<T>::get_key() const {
    return this->key;
}

template<>
int node_t<PizzaShop>::get_key()  const{
    return this->key;
}

template<>
int node_t<Vector<node_t<Vector<PizzaShop>>>>::get_key() const {
    return this->key;
}

template<class T>
T node_t<T>::get_value() {
    return this->value;
}

template<>
PizzaShop node_t<PizzaShop>::get_value()  {
    return this->value;
}

template<>
Neighberhood node_t<Neighberhood>::get_value()  {
    return this->value;
}


template<>
Vector<PizzaShop> node_t<Vector<PizzaShop>>::get_value() {
    return this->value;
}


template<>
Vector<Neighberhood> node_t<Vector<Neighberhood>>::get_value() {
    return this->value;
}

template<>
Vector<node_t<Vector<PizzaShop>>> node_t<Vector<node_t<Vector<PizzaShop>>>>::get_value()  {
    return this->value;
}

template<class T>
node_t<T>* node_t<T>::get_next() const {
    return this->next;
}

template<>
node_t<PizzaShop>* node_t<PizzaShop>::get_next() const {
    return this->next;
}

template <>
node_t<Vector<node_t<Vector<PizzaShop>>>>* node_t<Vector<node_t<Vector<PizzaShop>>>>::get_next() const {
    return this->next;
}

template <class T>
Linkedlist<T>::Linkedlist() : first(nullptr), last(nullptr), size(0) {}

template<>
Linkedlist<PizzaShop>::Linkedlist() : first(nullptr), last(nullptr), size(0) {}

template<>
Linkedlist<Vector<node_t<Vector<PizzaShop>>>>::Linkedlist() : first(nullptr), last(nullptr), size(0) {}

template<>
Linkedlist<Neighberhood>::Linkedlist() : first(nullptr), last(nullptr), size(0) {}


Linkedlist<KDTree>::Linkedlist(node_t<KDTree>* _first) {
    node_t<KDTree>* tmp = _first;
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

template<>
Linkedlist<PizzaShop>::Linkedlist(const Linkedlist<PizzaShop> &other) {
    node_t<PizzaShop>* itr = other.first;
    node_t<PizzaShop>* this_first = new node_t<PizzaShop>(other.first->key,nullptr,other.first->value);
    node_t<PizzaShop>* tmp = this_first;
    while(itr->next) {
        itr = itr->next;
        tmp->next = new node_t<PizzaShop>(itr->key, nullptr,itr->value);
        tmp = tmp->next;
    }
    this->first = this_first;
    this->last = tmp;
    this->size = other.size;
}


Linkedlist<KDTree>::Linkedlist(const Linkedlist<KDTree> &other)  {
    node_t<KDTree>* itr = other.first;
    node_t<KDTree>* this_first = new node_t<KDTree>(other.first->key,nullptr,other.first->value);
    node_t<KDTree>* tmp = this_first;
    while(itr->next) {
        itr = itr->next;
        tmp->next = new node_t<KDTree>(itr->key, nullptr,itr->value);
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


void Linkedlist<KDTree>::push_back(int key, KDTree value) {
    node_t<KDTree>* new_node = new node_t<KDTree>(key,nullptr,value);
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

template<>
void Linkedlist<Vector<node_t<Vector<PizzaShop>>>>::push_back(int key,Vector<node_t<Vector<PizzaShop>>> value) {
    node_t<Vector<node_t<Vector<PizzaShop>>>>* new_node = new node_t<Vector<node_t<Vector<PizzaShop>>>>(key,nullptr,value);
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

template<>
void Linkedlist<PizzaShop>::push_back(int key,PizzaShop value) {
    node_t<PizzaShop>* new_node = new node_t<PizzaShop>(key, nullptr,value);
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


template<>
void Linkedlist<Neighberhood>::push_back(int key,Neighberhood value) {
    node_t<Neighberhood>* new_node = new node_t<Neighberhood>(key, nullptr,value);
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

template<>
node_t<PizzaShop>* Linkedlist<PizzaShop>::search(int _key) {
    node_t<PizzaShop>* tmp = this->first;
    while(tmp) {
        if(tmp->key == _key)
            break;
        tmp = tmp->next;
    }
    return tmp;
}

template<>
node_t<Neighberhood>* Linkedlist<Neighberhood>::search(int _key) {
    node_t<Neighberhood>* tmp = this->first;
    while(tmp) {
        if(tmp->key == _key)
            break;
        tmp = tmp->next;
    }
    return tmp;
}


template<>
node_t<PizzaShop>* Linkedlist<PizzaShop>::search(int _key,PizzaShop val) {
    node_t<PizzaShop>* tmp = this->first;
    while(tmp) {
        if(tmp->key == _key && tmp->get_value().getName() == val.getName())
            break;
        tmp = tmp->next;
    }
    return tmp;
}



template<>
node_t<Vector<node_t<Vector<PizzaShop>>>>* Linkedlist<Vector<node_t<Vector<PizzaShop>>>>::search(int _key) {
    node_t<Vector<node_t<Vector<PizzaShop>>>>* tmp = this->first;
    while(tmp && tmp->value.getSize()) {
        if(tmp->value[0].get_key() == _key)
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

template<class T>
node_t<T>* Linkedlist<T>::get_first() const {
    return this->first;
}

template<>
node_t<PizzaShop>* Linkedlist<PizzaShop>::get_first() const {
    return this->first;
}

template<>
node_t<Vector<node_t<Vector<PizzaShop>>>> *Linkedlist<Vector<node_t<Vector<PizzaShop>>>>::get_first() const {
    return this->first;
}