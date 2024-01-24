#include "kdtree.h"
#include "heapsort.h"
KDTree::KDTree() : pos(0) {}
KDTree::KDTree(Vector<PizzaShop> &vec) : tree(vec), pos(0)
{
    build();
}
void KDTree::build()
{
    int size = tree.getSize();

    heapSort<PizzaShop>(tree, [](PizzaShop &one, PizzaShop &other) -> bool
                        { return one.getX() > other.getX(); });
    int median = size / 2;
    root = new Node *;
    *root = new Node(tree[median]);
    pos = 1;
    build(1, 0, median, *root); // left of it
    pos = 2;
    build(1, median + 1, size, *root); // right of it
    // for (int i = 0; i < size; i++)
    // {
    //     tree[i] = temp[i];
    // }
}
void KDTree::build(int depth, int begin, int end, Node *node)
{
    if (depth % 2 == 0) // X
    {
        heapSort<PizzaShop>(tree, begin, end,
                            [](PizzaShop &one, PizzaShop &other) -> bool
                            {
                                return one.getX() > other.getX();
                            });
        int median = ((end - begin) / 2) + begin;
        Node *t = new Node(tree[median], node);
        if (pos % 2) // left
        {
            node->setLeft(t);
            node = node->getLeft();
        }
        else // right
        {
            node->setRight(t);
            node = node->getRight();
        }
        // node = new Node(tree[median]);
        if (median > begin)
        {
            pos = (pos * 2) + 1;
            build(depth + 1, begin, median, node);
            pos /= 2;
        }
        if (median < end - 1)
        {
            pos = (pos * 2) + 2;
            build(depth + 1, median + 1, end, node);
            pos--;
            pos /= 2;
        }
    }
    else // Y
    {
        heapSort<PizzaShop>(tree, begin, end,
                            [](PizzaShop &one, PizzaShop &other) -> bool
                            {
                                return one.getY() > other.getY();
                            });
        int median = ((end - begin) / 2) + begin;
        Node *t = new Node(tree[median], node);
        if (pos % 2) // left
        {
            node->setLeft(t);
            node = node->getLeft();
        }
        else // right
        {
            node->setRight(t);
            node = node->getRight();
        }
        if (median > begin)
        {
            pos = (pos * 2) + 1;
            build(depth + 1, begin, median, node);
            pos /= 2;
        }
        if (median < end - 1)
        {
            pos = (pos * 2) + 2;
            build(depth + 1, median + 1, end, node);
            pos--;
            pos /= 2;
        }
    }
}
Vector<PizzaShop> &KDTree::getVec()
{
    return tree;
}
void KDTree::print()
{
    int height = log2(tree.getSize());
    int x = 0;
    for (int i = height; i >= 0; i--)
    {
        for (int j = 1; j < pow(2, i); j++)
        {
            cout << " ";
        }
        for (int j = 0; j < pow(2, height - i); j++)
        {
            if (x == tree.getSize())
            {
                return;
            }
            cout << tree[x].getName();
            x++;
            for (int k = 1; k < pow(2, i + 1); k++)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}
void KDTree::print(int line)
{
    for (int i = 0; i < line; i++)
    {
        for (int j = 1; j < pow(2, line - i); j++)
        {
            cout << " ";
        }
        nodePrinter(i, 0, *root, line);
        cout << endl;
    }
}
void KDTree::nodePrinter(int line, int depth, Node *node, int maxline)
{
    if (depth == line)
    {
        if (node != nullptr)
        {
            cout << node->getValue().getName();
        }
        else
        {
            cout << "#";
        }
        for (int i = 1; i < pow(2, maxline - depth + 1); i++)
        {
            cout << " ";
        }
    }
    else
    {
        // if (node->hasLeft())
        nodePrinter(line, depth + 1, node->getLeft(), maxline);
        // if (node->hasRight())
        nodePrinter(line, depth + 1, node->getRight(), maxline);
    }
}
bool KDTree::isBalanced() {}
int KDTree::findHeight() {}
int KDTree::findDepth(Node *node) {
    int depth = 0;
    Node* tmp = node;
    for(;tmp;depth++,tmp = tmp->getParent());
    return depth;
    //If depth odd then axis = x and if even then axis = y
}

Node* KDTree::findNearestNeighbor(Node* best_match, Node* point, Node *query, int depth) {
    int axis = depth % 2;
    Node* next_point = (point->getValue()[axis] <= point->getValue()[axis]) ? point->getLeft() : point->getRight();
    if((!point->hasLeft() || !point->hasRight()) && next_point == nullptr) return point;
    Node* tmp = findNearestNeighbor(best_match,next_point,query,depth + 1);
    Node* best = distance(tmp,query) > distance(query,best_match) ? best_match : tmp;
    if( distance(best,point) > abs(point->getValue()[axis] - query->getValue()[axis])) {
        Node* other = (next_point == point->getLeft()) ? point->getRight() : point->getLeft();
        if(other)
            tmp = distance(tmp,query) > distance(query,best_match) ? best_match : tmp;
    }
    if(distance(tmp,query) > distance(query,best)) return best;
    else return tmp;
}

Node* KDTree::getRoot() {
    return *(root);
}

/*******************************Functions************************************/

float distance(Node* first,Node* second) {
    if(first == nullptr || second == nullptr) return 10000000;
    auto dis = pow((first->getValue()[1]-second->getValue()[1]),2) +
               pow((first->getValue()[0]-second->getValue()[0]),2);
    return sqrt(dis);
}
