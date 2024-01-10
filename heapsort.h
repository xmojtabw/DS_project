#ifndef HEAPSORT_H
#define HEAPSORT_H
#include "pizzashop.h"

int findStartIndex(int size);
template <typename T>
void heapfy(Vector<T> &tree, bool (*compare)(T &one, T &other), int index, int size, int begin);
template <typename T>
void heapSort(Vector<T> &tree, bool (*compare)(T &one, T &other));
template <typename T>
void heapSort(Vector<T> &tree, int begin, int end, bool (*compare)(T &one, T &other));
template <typename T>
void heapSort(Vector<T> &tree);
#include "heapsort.cpp"
#endif