#ifndef _KDTREE_H_
#define _KDTREE_H_
#include "vectorT.h"
// #include "pizzashop.h"
#include "node.h"
class KDTree
{
private:
    Vector<PizzaShop> tree;

    Node **root = nullptr;
    //------------//
    int pos;

public:
    KDTree();
    KDTree(Vector<PizzaShop> &vec);
    void build();
    void build(int depth, int begin, int end, Node *node);
    Vector<PizzaShop> &getVec();
    void print();
    void print(int line);
    void nodePrinter(int line, int depth, Node *node, int maxline);
    bool isBalanced();
    int findHeight();
};
#endif