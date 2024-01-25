#ifndef _KDTREE_H_
#define _KDTREE_H_
#include <math.h>
#include <cmath>
#include "vectorT.h"
#include <functional>
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
    void build(int depth, Vector<PizzaShop> &x_sorted, Vector<PizzaShop> &y_sorted, Node *node);
    void split(Vector<PizzaShop> &vec, Vector<PizzaShop> &left, Vector<PizzaShop> &right, std::function<int(PizzaShop &val)> spliter);
    void split(Vector<PizzaShop> &vec, Vector<PizzaShop> &left, Vector<PizzaShop> &right, int median);
    Node *getRoot();
    Vector<PizzaShop> &getVec();
    void print();
    void print(int line);
    void nodePrinter(int line, int depth, Node *node, int maxline);
    bool isBalanced();
    int findHeight();
    int findDepth(Node*);
    Node* findNearestNeighbor(Node* best_match,Node* point,Node* query,int depth);
    Node* getRoot();
};

/*******************************Functions************************************/
float distance(Node* first,Node* second);
#endif