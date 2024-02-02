#include "node.h"

Node::Node() {}
Node::Node(PizzaShop &ps, Node *p) : value(ps), parent(p) {}
void Node::setLeft(Node *l)
{
    left = l;
    left->parent = this;
    left_h = 1;
}
void Node::setRight(Node *r)
{
    right = r;
    right->parent = this;
    right_h = 1;
}
void Node::setParent(Node *p) { parent = p; }
bool Node::isLeaf() { return (right == nullptr && left == nullptr); }
bool Node::isRoot() { return parent == nullptr; }
bool Node::hasLeft() { return left != nullptr; }
bool Node::hasRight() { return right != nullptr; }
void Node::setLeftH(int val) { left_h = val; }
void Node::setRightH(int val) { right_h = val; }
int Node::getRightH() { return right_h; }
int Node::getLeftH() { return left_h; }
void Node::delLeaf()
{
    if (parent)
    {
        if (parent->left == this)
        {
            parent->left_h = 0;
            parent->left = nullptr;
        }
        else
        {
            parent->right_h = 0;
            parent->right = nullptr;
        }
    }
}
Node *Node::getLeft() { return left; }
Node *Node::getRight() { return right; }
Node *Node::getParent() { return parent; }
PizzaShop &Node::getValue() { return value; }
void Node::copyNode(Node *n)
{
    value = n->getValue();
}
// Node::~Node()
// {
//     if (left)
//         delete left;
//     if (right)
//         delete right;
// }