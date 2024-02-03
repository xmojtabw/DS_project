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
    setHeight(*root);
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
    return x_s_tree;
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
int KDTree::setHeight(Node *node)
{ // O(n)
    if (node->isLeaf())
    {
        // no need to set right_h and left_h to 0 beacause they are
        // if not uncomment these
        node->setLeftH(0);
        node->setRightH(0);
        return 1;
    }
    if (node->hasRight())
    {
        node->setRightH(setHeight(node->getRight()));
    }
    if (node->hasLeft())
    {
        node->setLeftH(setHeight(node->getLeft()));
    }
    return (((node->getRightH() > node->getLeftH()) ? node->getRightH() : node->getLeftH()) + 1);
}
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
      Node* next_point = (point->getValue()[axis] <= point->getValue()[axis]) ? point->getLeft() : point->getRight();
    if((!point->hasLeft() || !point->hasRight()) && next_point == nullptr) return point;
    Node* tmp = findNearestNeighbor(best_match,next_point,query,depth + 1);
    Node* best = distance(tmp,query) > distance(query,best_match) ? best_match : tmp;
    if( distance(best,point) > abs(point->getValue()[axis] - query->getValue()[axis])) {
        Node* other = (next_point == point->getLeft()) ? point->getRight() : point->getLeft();
        tmp = distance(query,point) > distance(query,best) ? best : point;
        if(other)
            tmp = distance(tmp,query) > distance(query,other) ? other : tmp;
    }
    if(distance(tmp,query) > distance(query,best)) return best;
    else return tmp;
}


void KDTree::insertToTree(PizzaShop &value)
{
    int res = insertToTree(*root, value, 0);
    // adding in sorted vectors
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

    if (res < 0)
    {
        build(); // its not balance anymore
    }
}
int KDTree::insertToTree(Node *node, PizzaShop &value, int depth)
{
    if (node == nullptr)
    {
        // adding to root
        node = new Node(value);
    }
    int h = 0;
    if (depth % 2) // Y
    {
        if (node->getValue().getY() < value.getY())
        { // goes in right
            if (node->hasRight())
            {
                h = insertToTree(node->getRight(), value, depth + 1);
                if (h < 0) // it's a flag that shows tree has been unbalanced
                {
                    return -1;
                }
                else
                { // since tree is still balance
                    node->setRightH(h);
                }
            }
            else
            {
                Node *t = new Node(value);
                node->setRight(t);
            }
        }
        else if (node->getValue().getY() > value.getY())
        { // goes in left
            if (node->hasLeft())
            {
                h = insertToTree(node->getLeft(), value, depth + 1);
                if (h < 0) // it's a flag that shows tree has been unbalanced
                {
                    return -1;
                }
                else
                { // since tree is still balance
                    node->setLeftH(h);
                }
            }
            else
            {
                Node *t = new Node(value);
                node->setLeft(t);
            }
        }
        else // same Y
        {
            if (node->getValue().getX() < value.getX())
            { // goes in right
                if (node->hasRight())
                {
                    h = insertToTree(node->getRight(), value, depth + 1);
                    if (h < 0) // it's a flag that shows tree has been unbalanced
                    {
                        return -1;
                    }
                    else
                    { // since tree is still balance
                        node->setRightH(h);
                    }
                }
                else
                {
                    Node *t = new Node(value);
                    node->setRight(t);
                }
            }
            else
            { // goes in left
                if (node->hasLeft())
                {
                    h = insertToTree(node->getLeft(), value, depth + 1);
                    if (h < 0) // it's a flag that shows tree has been unbalanced
                    {
                        return -1;
                    }
                    else
                    { // since tree is still balance
                        node->setLeftH(h);
                    }
                }
                else
                {
                    Node *t = new Node(value);
                    node->setLeft(t);
                }
            }
        }
    }
    else // X
    {
        if (node->getValue().getX() < value.getX())
        { // goes in right
            if (node->hasRight())
            {
                h = insertToTree(node->getRight(), value, depth + 1);
                if (h < 0) // it's a flag that shows tree has been unbalanced
                {
                    return -1;
                }
                else
                { // since tree is still balance
                    node->setRightH(h);
                }
            }
            else
            {
                Node *t = new Node(value);
                node->setRight(t);
            }
        }
        else if (node->getValue().getX() > value.getX())
        { // goes in left
            if (node->hasLeft())
            {
                h = insertToTree(node->getLeft(), value, depth + 1);
                if (h < 0) // it's a flag that shows tree has been unbalanced
                {
                    return -1;
                }
                else
                { // since tree is still balance
                    node->setLeftH(h);
                }
            }
            else
            {
                Node *t = new Node(value);
                node->setLeft(t);
            }
        }
        else // same X
        {
            if (node->getValue().getY() < value.getY())
            { // goes in right
                if (node->hasRight())
                {
                    h = insertToTree(node->getRight(), value, depth + 1);
                    if (h < 0) // it's a flag that shows tree has been unbalanced
                    {
                        return -1;
                    }
                    else
                    { // since tree is still balance
                        node->setRightH(h);
                    }
                }
                else
                {
                    Node *t = new Node(value);
                    node->setRight(t);
                }
            }
            else
            { // goes in left
                if (node->hasLeft())
                {
                    h = insertToTree(node->getLeft(), value, depth + 1);
                    if (h < 0) // it's a flag that shows tree has been unbalanced
                    {
                        return -1;
                    }
                    else
                    { // since tree is still balance
                        node->setLeftH(h);
                    }
                }
                else
                {
                    Node *t = new Node(value);
                    node->setLeft(t);
                }
            }
        }
    }
    int avl = node->getLeftH() - node->getRightH();
    if (avl * avl > 1)
    {
        // unbalance
        return -1;
    }
    else
    {
        if (node->getLeftH() > node->getRightH())
        {
            return node->getLeftH() + 1;
        }
        else
        {
            return node->getRightH() + 1;
        }
    }
}
void KDTree::removeFromTree(Node *node)
{
    x_s_tree.erase(node->getValue());
    y_s_tree.erase(node->getValue());
    int res = removeRec(node);
    if (res < 0)
        build();
}
int KDTree::removeRec(Node *node)
{
    if (node->isLeaf())
    {
        Node *p = node->getParent();
        Node *n = node;
        node->delLeaf();
        int max_h = 0;
        while (p != nullptr)
        {
            if (p->getRight() == n) // its right child
            {
                p->setRightH(max_h);
            }
            else
            {
                p->setLeftH(max_h);
            }
            int avl = p->getLeftH() - p->getRightH();
            if (avl * avl > 2)
            {
                return -1; // flag to show it's unbalance
            }
            // update max_h
            if (avl)
            {
                // right is bigger
                max_h = p->getRightH();
            }
            else
            {
                max_h = p->getLeftH();
            }
            n = p;
            p = p->getParent();
        }
        return 1; // no unbalance
    }
    else if (node->hasRight())
    {
        int axis = getHeight(node) % 2;
        Node *min = findmin(node->getRight(), 0, axis);
        node->copyNode(min);
        return removeRec(min);
    }
    else
    {
        // it has only one in left
        node->copyNode(node->getLeft());
        return removeRec(node->getLeft());
    }
}
Node *KDTree::findmin(Node *subtree, int depth, int axis)
{
    if (depth % 2) // Y
    {
        if (axis == 0) // X
        {
            // have to go into both
            Node *min_left;
            Node *min_right;
            if (subtree->hasRight())
            {
                min_left = findmin(subtree->getLeft(), depth + 1, axis);
            }
            if (subtree->hasLeft())
            {
                min_right = findmin(subtree->getRight(), depth + 1, axis);
            }
            if (min_right->getValue().compareByX(min_left->getValue()))
            { // min left is smaller
                if (subtree->getValue().compareByX(min_left->getValue()))
                {
                    // minleft is smaller
                    return min_left;
                }
                else
                { // subtree is smaller
                    return subtree;
                }
            }
            else
            { // min right is smaller
                if (subtree->getValue().compareByX(min_right->getValue()))
                {
                    return min_right;
                }
                else
                {
                    return subtree;
                }
            }
        }
        else
        {
            // if axis is y only left subtree has minimum if it has left
            if (subtree->hasLeft())
            {
                return findmin(subtree->getLeft(), depth + 1, axis);
            }
            else // since it doesn't have left , it's min
            {
                return subtree;
            }
        }
    }
    else // X
    {
        if (axis == 1) // Y
        {
            // have to go into both
            Node *min_left;
            Node *min_right;
            if (subtree->hasRight())
            {
                min_left = findmin(subtree->getLeft(), depth + 1, axis);
            }
            if (subtree->hasLeft())
            {
                min_right = findmin(subtree->getRight(), depth + 1, axis);
            }
            if (min_right->getValue().compareByY(min_left->getValue()))
            { // min left is smaller
                if (subtree->getValue().compareByY(min_left->getValue()))
                {
                    // minleft is smaller
                    return min_left;
                }
                else
                { // subtree is smaller
                    return subtree;
                }
            }
            else
            { // min right is smaller
                if (subtree->getValue().compareByY(min_right->getValue()))
                {
                    return min_right;
                }
                else
                {
                    return subtree;
                }
            }
        }
        else
        {
            // if axis is X only left subtree has minimum if it has left
            if (subtree->hasLeft())
            {
                return findmin(subtree->getLeft(), depth + 1, axis);
            }
            else // since it doesn't have left , it's min
            {
                return subtree;
            }
        }
    }
}
int KDTree::getHeight(Node *node)
{
    Node *it = node;
    int h = 0;
    while (true)
    {
        it = it->getParent();
        if (!it) // if it is nullptr
        {
            return h;
        }
        h++;
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
