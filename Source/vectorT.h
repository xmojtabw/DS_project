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
public:
    T *ptr;
    int capacity;
    int size;
    Vector();
    Vector(int size);
    Vector(T *p, int size);
    Vector(const Vector<T>& other);
    Vector(const initializer_list<pair<string, function<void(Vector<std::string>)>>> &values);
    void pushBack(T &value);
    void popBack();
    void popFront();
    int getSize() const;
    T* begin();
    T* end();
    T &operator[](int index);
    void erase(int index);
    void erase(T &value);
    void insert(T &value, int index);
    void insert(T &value, bool (*cond)(T &eachone, T &value));
};
#include "vectorT.cpp" //im here because of link error
#endif