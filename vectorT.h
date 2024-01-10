#ifndef VECTORT_H
#define VECTORT_H
#include <stdexcept>
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
    void pushBack(T value);
    void popBack();
    int getSize() const;
    T &operator[](int index);
};
#include "vectorT.cpp" //im here because of link error
#endif