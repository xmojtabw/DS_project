#include "vectorT.h"

template <class T>
Vector<T>::Vector() : size(0), capacity(3)
{
    ptr = new T[capacity];
}

template <class T>
Vector<T>::Vector(int size) : size(size), capacity(2 * size)
{
    ptr = new T[capacity];
}

template <class T>
Vector<T>::Vector(T *p, int _size) : size(_size), capacity(2 * size)
{
    ptr = new T[capacity];
    for (int i = 0; i < _size; i++)
    {
        ptr[i] = p[i];
    }
}

template <class T>
void Vector<T>::pushBack(T value)
{
    if (size == capacity)
    {
        capacity *= 2;
        T *second_space = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            second_space[i] = ptr[i];
        }
        delete[] ptr;
        ptr = second_space;
    }
    ptr[size] = value;
    size++;
}

template <class T>
void Vector<T>::popBack()
{
    size--;
}

template <class T>
int Vector<T>::getSize() const
{
    return size;
}

template <class T>
T &Vector<T>::operator[](int index)
{
    if (index >= 0 && index < size)
    {
        return ptr[index];
    }
    else
    {
        throw std::out_of_range("wrong index");
    }
}
