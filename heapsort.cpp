#include "heapsort.h"
#include <cmath>
template <typename T>
int findStartIndex(Vector<T> &tree)
{
    // need to be better
    return (tree.getSize() - 1);
}
template <typename T>
void heapfy(Vector<T> &tree, bool (*compare)(T &one, T &other), int index, int size)
{
    int left_index = (2 * index) + 1;
    int right_index = (2 * index) + 2;
    if (right_index < size) // if both child exist
    {
        if (compare(tree[left_index], tree[right_index]))
        {
            if (compare(tree[left_index], tree[index]))
            {
                swap(tree[left_index], tree[index]);
                heapfy(tree, compare, left_index, size);
            }
        }
        else
        {
            if (compare(tree[right_index], tree[index]))
            {
                swap(tree[right_index], tree[index]);
                heapfy(tree, compare, right_index, size);
            }
        }
    }
    else if (left_index < size) // if left child exist only
    {
        if (compare(tree[left_index], tree[index]))
        {
            swap(tree[left_index], tree[index]);
        }
    }
    // else--> no child exist --> no heapfy needed
}
template <typename T>
void heapSort(Vector<T> &tree, bool (*compare)(T &one, T &other))
{
    int size = tree.getSize();
    for (int i = findStartIndex(tree); i > -1; i--)
    {
        heapfy(tree, compare, i, size);
    }
    for (int i = 0; i < tree.getSize() - 1; i++)
    {
        swap(tree[size - 1], tree[0]);
        size--;
        heapfy(tree, compare, 0, size);
    }
};

template <typename T>
void heapSort(Vector<T> &tree){};
