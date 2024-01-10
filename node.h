#ifndef _NODE_H
#define _NODE_H
#include "pizzashop.h"
class Node
{
private:
    PizzaShop value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    Node *next = nullptr; // for hashing
public:
    Node();
    Node(PizzaShop &ps, Node *parent = nullptr);
    void setLeft(Node *left);
    void setRight(Node *right);
    void setParent(Node *right);
    bool isLeaf();
    bool isRoot();
    bool hasLeft();
    bool hasRight();
    Node *getRight();
    Node *getLeft();
    Node *getParent();
    PizzaShop &getValue();
};
#endif