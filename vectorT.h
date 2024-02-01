#ifndef VECTORT_H
#define VECTORT_H
#include <stdexcept>
#include <utility>
#include <functional>
#include <initializer_list>
using namespace std;
template <class T>
class Vector
{
private:
    T *ptr;
    int capacity;
    int size;

public:
    Vector();
    Vector(int size);
    Vector(T *p, int size);
    Vector(const Vector<T> &other);
    Vector(const initializer_list<pair<string, function<void(Vector<std::string>)>>> &values);
    void pushBack(T &value);
    void popBack();
    void popFront();
    int getSize() const;
    T &operator[](int index);
};
#include "vectorT.cpp" //im here because of link error
#endif