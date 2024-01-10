#include "node.h"

Node::Node() {}
Node::Node(PizzaShop &ps, Node *p) : value(ps), parent(p) {}
void Node::setLeft(Node *l) { left = l; }
void Node::setRight(Node *r) { right = r; }
void Node::setParent(Node *p) { parent = p; }
bool Node::isLeaf() { return (right == nullptr && left == nullptr); }
bool Node::isRoot() { return parent == nullptr; }
bool Node::hasLeft() { return left != nullptr; }
bool Node::hasRight() { return right != nullptr; }
Node *Node::getLeft() { return left; }
Node *Node::getRight() { return right; }
Node *Node::getParent() { return parent; }
PizzaShop &Node::getValue() { return value; }