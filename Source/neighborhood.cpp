#include "neighberhood.h"
Neighberhood::Neighberhood(string name, int l_u_x, int l_u_y,
                           int r_u_x, int r_u_y, int r_d_x, int r_d_y,
                           int l_d_x, int l_d_y) : name(name), max_x(r_u_x),
                                                   min_x(l_u_x), max_y(l_u_y), min_y(l_d_y)
{
}
Vector<PizzaShop> &Neighberhood::searchInKdtree(KDTree &tree)
{
    Node *root = tree.getRoot();
    searchInKdtree(root, 0);
    return shops;
}
void Neighberhood::searchInKdtree(Node *node, int depth)
{
    if (node == nullptr)
        return;

    if (depth % 2) // Y
    {
        int y = node->getValue().getY();
        if (y > max_y)
        {
            // left of it still can be in the neighbor
            searchInKdtree(node->getLeft(), depth + 1);
        }
        else if (y < min_y)
        {
            // right of it still can be in the neighbor
            searchInKdtree(node->getRight(), depth + 1);
        }
        else // y is between min and max
        {
            // both can be in neighbor
            searchInKdtree(node->getLeft(), depth + 1);
            searchInKdtree(node->getRight(), depth + 1);
            if (isInXRange(node))
            {
                shops.pushBack(node->getValue());
            }
        }
    }
    else // X
    {
        int x = node->getValue().getX();
        if (x > max_x)
        {
            // left of it still can be in the neighbor
            searchInKdtree(node->getLeft(), depth + 1);
        }
        else if (x < min_x)
        {
            // right of it still can be in the neighbor
            searchInKdtree(node->getRight(), depth + 1);
        }
        else // x is between min and max
        {
            // both can be in neighbor
            searchInKdtree(node->getLeft(), depth + 1);
            searchInKdtree(node->getRight(), depth + 1);
            if (isInYRange(node))
            {
                shops.pushBack(node->getValue());
            }
        }
    }
}
bool Neighberhood::isInYRange(Node *node)
{
    int y = node->getValue().getY();
    return (y <= max_y && y >= min_y);
}
bool Neighberhood::isInXRange(Node *node)
{
    int x = node->getValue().getX();
    return (x <= max_x && x >= min_x);
}
string Neighberhood::get_name() const {
    return name;
}