#include "vectorT.h"

template <class T>
Vector<T>::Vector() : capacity(3), size(0)
{
    ptr = new T[capacity];
}
template <class T>
Vector<T>::Vector(int size) : capacity(2 * size), size(size)
{
    ptr = new T[capacity];
}
template <class T>
Vector<T>::Vector(T *p, int _size) : capacity(2 * size), size(_size)
{
    ptr = new T[capacity];
    for (int i = 0; i < _size; i++)
    {
        ptr[i] = p[i];
    }
}
template <class T>
Vector<T>::Vector(const Vector<T> &other) : capacity(other.capacity), size(other.size)
{
    ptr = new T[capacity];
    for (int i = 0; i < size; i++)
    {
        ptr[i] = other.ptr[i];
    }
}
template <class T>
void Vector<T>::pushBack(T &value)
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
    if (size)
    {
        size--;
    }
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
template <class T>
void Vector<T>::erase(int index)
{
    if (index >= 0 && index < size)
    {
        for (int i = index; i + 1 < size; i++)
        {
            ptr[i] = ptr[i + 1];
        }
        size--;
    }
}
template <class T>
void Vector<T>::erase(T &value)
{
    for (int i = 0; i < size; i++)
    {
        if (ptr[i] == value)
        {
            erase(i);
            return;
        }
    }
}
template <class T>
void Vector<T>::insert(T &value, int index)
{
    if (index >= 0 && index <= size)
    {
        if (index == size)
        {
            pushBack(value);
        }
        else
        {
            if (size == capacity)
            {
                capacity *= 2;
                T *second_space = new T[capacity];
                for (int i = 0; i < index; i++)
                {
                    second_space[i] = ptr[i];
                }
                delete[] ptr;
                ptr = second_space;
            }
            size++;
            for (int i = index + 1; i < size; i++)
            {
                ptr[i] = ptr[i - 1];
            }
            ptr[index] = value;
        }
    }
}
template <class T>
void Vector<T>::insert(T &value, bool (*cond)(T &eachone, T &value))
{
    if (size == capacity)
    {
        capacity *= 2;
        T *second_space = new T[capacity];
        int i = 0;
        for (; i < size; i++)
        {
            if (!cond(ptr[i], value)) // when value is smaller than ptr[i]
            {
                break;
            }
            second_space[i] = ptr[i];
        }
        second_space[i] = value;
        for (; i < size; i++)
        {
            second_space[i + 1] = ptr[i];
        }
        size++;
        delete[] ptr;
        ptr = second_space;
    }
    else
    {
        int i = size - 1;
        for (; i > 0; i--)
        {
            if (cond(ptr[i], value)) // when value is bigger than ptr[i]
            {
                ptr[i + 1] = value;
                break;
            }
            ptr[i + 1] = ptr[i];
        }
        size++;
    }
}