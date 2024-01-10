#include "heapsort.h"
#include <cmath>

int findStartIndex(int size)
{
    // need to be better
    return (size - 1);
}
template <typename T>
void heapfy(Vector<T> &tree, bool (*compare)(T &one, T &other), int index, int size, int begin)
{
    int left_index = (2 * (index - begin)) + 1 + begin;
    int right_index = (2 * (index - begin)) + 2 + begin;
    if (right_index < size) // if both child exist
    {
        if (compare(tree[left_index], tree[right_index]))
        {
            if (compare(tree[left_index], tree[index]))
            {
                swap(tree[left_index], tree[index]);
                heapfy(tree, compare, left_index, size, begin);
            }
        }
        else
        {
            if (compare(tree[right_index], tree[index]))
            {
                swap(tree[right_index], tree[index]);
                heapfy(tree, compare, right_index, size, begin);
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
template <typename T> // sort all of the tree(from 0 to end)
void heapSort(Vector<T> &tree, bool (*compare)(T &one, T &other))
{
    int size = tree.getSize();
    for (int i = findStartIndex(size); i > -1; i--)
    {
        heapfy(tree, compare, i, size, 0);
    }
    for (int i = 0; i < tree.getSize() - 1; i++)
    {
        swap(tree[size - 1], tree[0]);
        size--;
        heapfy(tree, compare, 0, size);
    }
}
template <typename T>
void heapSort(Vector<T> &tree, int begin, int end, bool (*compare)(T &one, T &other))
{
    // creating heap tree from begin index to end index
    for (int i = findStartIndex(end - begin) + begin; i >= begin; i--)
    {
        // heapfy from i to end
        heapfy(tree, compare, i, end, begin);
    }
    // swaping the root(begin) with end of it(i)
    // then heapfy the root(begin) again until(i)
    for (int i = end - 1; i > begin; i--)
    {
        swap(tree[i], tree[begin]);
        // heapfy from begin to i
        heapfy(tree, compare, begin, i, begin);
    }
};

template <typename T>
void heapSort(Vector<T> &tree) // sort entire tree if "<" is defined
{
    heapSort(tree, 0, tree.getSize(), [](T &one, T &other) -> bool
             { return (one < other); });
}
