#include "kdtree.h"
// #include "heapsort.h"
KDTree::KDTree() : pos(0) {}
KDTree::KDTree(Vector<PizzaShop> &vec) : tree(vec), x_s_tree(vec), y_s_tree(vec), pos(0)
{

    heapSort<PizzaShop>(x_s_tree, [](PizzaShop &one, PizzaShop &other) -> bool
                        { 
                            if(one.getX() > other.getX())return true;
                            if(one.getX() < other.getX())return false;
                            //if the have same X sort it with y 
                            return one.getY() > other.getY(); });
    heapSort<PizzaShop>(y_s_tree, [](PizzaShop &one, PizzaShop &other) -> bool
                        {                       
                            if(one.getY() > other.getY())return true;
                            if(one.getY() < other.getY())return false;
                            //if the have same X sort it with y 
                            return one.getX() > other.getX(); });

    build();
}
void KDTree::build()
{
    int size = x_s_tree.getSize();
    int median = size / 2;

    // sorting both vectors with x-axis and y-axis
    PizzaShop &median_val = x_s_tree[median];
    if (root)
        delete root;
    root = new Node *;
    *root = new Node(median_val);

    Vector<PizzaShop> left_x_sorted;
    Vector<PizzaShop> left_y_sorted;
    Vector<PizzaShop> right_x_sorted;
    Vector<PizzaShop> right_y_sorted;

    split(x_s_tree, left_x_sorted, right_x_sorted, median);
    // bool lambd = [tree]()
    split(y_s_tree, left_y_sorted, right_y_sorted,
          [median_val](PizzaShop &val) -> int
          {
              if (val.getX() > median_val.getX())return 1;
              if (val.getX() < median_val.getX())return -1;
              // since the have same X with median:
              if (val.getY() > median_val.getY())return 1; // after median
              if (val.getY() < median_val.getY())return -1; // before median
              else return 0; }); /// its median
    pos = 1;
    build(1, left_x_sorted, left_y_sorted, *root); // build left of it
    pos = 2;
    build(1, right_x_sorted, right_y_sorted, *root); // build right of it
}
void KDTree::build(int depth, Vector<PizzaShop> &x_sorted, Vector<PizzaShop> &y_sorted, Node *node)
{
    if (x_sorted.getSize() == 0)
        return;
    Vector<PizzaShop> left_x_sorted;
    Vector<PizzaShop> left_y_sorted;
    Vector<PizzaShop> right_x_sorted;
    Vector<PizzaShop> right_y_sorted;
    Node *t;
    int median = x_sorted.getSize() / 2;
    if (depth % 2) // Y
    {
        PizzaShop &median_val = y_sorted[median];
        t = new Node(median_val);
        split(y_sorted, left_y_sorted, right_y_sorted, median);
        split(x_sorted, left_x_sorted, right_x_sorted,
              [median_val](PizzaShop &val) -> int
              {
                  if (val.getY() > median_val.getY())return 1;
                  if (val.getY() < median_val.getY())return -1;
                  // since the have same Y with median:
                  if (val.getX() > median_val.getX())return 1; // after median
                  if (val.getX() < median_val.getX())return -1; // before median
                  else return 0; }); // its median
    }
    else // X
    {
        PizzaShop &median_val = x_sorted[median];
        t = new Node(median_val);
        split(x_sorted, left_x_sorted, right_x_sorted, median);
        split(y_sorted, left_y_sorted, right_y_sorted,
              [median_val](PizzaShop &val) -> int
              {
                  if (val.getX() > median_val.getX())return 1;
                  if (val.getX() < median_val.getX())return -1;
                  // since the have same X with median:
                  if (val.getY() > median_val.getY())return 1; // after median
                  if (val.getY() < median_val.getY())return -1; // before median
                  else return 0; }); // its median
    }
    if (pos % 2) // if its a right child
    {
        node->setLeft(t);
        node = node->getLeft();
    }
    else // left child
    {
        node->setRight(t);
        node = node->getRight();
    }
    pos = (pos * 2) + 1;
    build(depth + 1, left_x_sorted, left_y_sorted, node);
    pos /= 2;
    pos = (pos * 2) + 2;
    build(depth + 1, right_x_sorted, right_y_sorted, node);
    pos--;
    pos /= 2;
}
void KDTree::split(Vector<PizzaShop> &vec, Vector<PizzaShop> &left, Vector<PizzaShop> &right, std::function<int(PizzaShop &val)> spliter)
{
    for (int i = 0; i < vec.getSize(); i++)
    {
        switch (spliter(vec[i]))
        {
        case -1:
            left.pushBack(vec[i]);
            break;
        case 1:
            right.pushBack(vec[i]);
        default: //--> 0 its median
            break;
        }
    }
}
void KDTree::split(Vector<PizzaShop> &vec, Vector<PizzaShop> &left, Vector<PizzaShop> &right, int median)
{
    for (int i = 0; i < median; i++)
    {
        left.pushBack(vec[i]);
    }
    for (int i = median + 1; i < vec.getSize(); i++)
    {
        right.pushBack(vec[i]);
    }
}
Node *KDTree::getRoot() { return *root; }
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
int KDTree::findDepth(Node *node)
{
    int depth = 0;
    Node *tmp = node;
    for (; tmp; depth++, tmp = tmp->getParent())
        ;
    return depth;
    // If depth odd then axis = x and if even then axis = y
}

Node *KDTree::findNearestNeighbor(Node *best_match, Node *point, Node *query, int depth)
{
    int axis = depth % 2;
    Node *next_point = (point->getValue()[axis] <= point->getValue()[axis]) ? point->getLeft() : point->getRight();
    if ((!point->hasLeft() || !point->hasRight()) && next_point == nullptr)
        return point;
    Node *tmp = findNearestNeighbor(best_match, next_point, query, depth + 1);
    Node *best = distance(tmp, query) > distance(query, best_match) ? best_match : tmp;
    if (distance(best, point) > abs(point->getValue()[axis] - query->getValue()[axis]))
    {
        Node *other = (next_point == point->getLeft()) ? point->getRight() : point->getLeft();
        if (other)
            tmp = distance(tmp, query) > distance(query, best_match) ? best_match : tmp;
    }
    if (distance(tmp, query) > distance(query, best))
        return best;
    else
        return tmp;
}
void KDTree::insertToTree(PizzaShop &value)
{
    x_s_tree.insert(value, [](PizzaShop &eachone, PizzaShop &val) -> bool
                    {
        if(eachone.getX() < val.getX())return true;
        else if(eachone.getX() >val.getX())return false;
        else
        {
            if(eachone.getY() < val.getY()) return true;
            else return false;
        } });
    y_s_tree.insert(value, [](PizzaShop &eachone, PizzaShop &val) -> bool
                    {
        if(eachone.getY() < val.getY())return true;
        else if(eachone.getY() >val.getY())return false;
        else
        {
            if(eachone.getX() < val.getX()) return true;
            else return false;
        } });
    build();
}
void KDTree::removeFromTree(PizzaShop &value)
{
    x_s_tree.erase(value);
    y_s_tree.erase(value);
    build();
}
/*******************************Functions************************************/

float distance(Node *first, Node *second)
{
    if (first == nullptr || second == nullptr)
        return 10000000;
    auto dis = pow((first->getValue()[1] - second->getValue()[1]), 2) +
               pow((first->getValue()[0] - second->getValue()[0]), 2);
    return sqrt(dis);
}
