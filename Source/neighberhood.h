#ifndef NEIGHBERHOOD_H
#define NEIGHBERHOOD_H
#include <iostream>
#include "kdtree.h"
#include "vectorT.h"
using namespace std;
class Neighberhood
{
private:
    string name;
    int max_x;
    int min_x;
    int max_y;
    int min_y;
    Vector<PizzaShop> shops;

public:
    Neighberhood() = default;
    // l:left r:right u:up d:down
    Neighberhood(string name, int l_u_x, int l_u_y,
                 int r_u_x, int r_u_y, int r_d_x, int r_d_y,
                 int l_d_x, int l_d_y);
    Neighberhood(const Neighberhood& other) = default;
    Neighberhood &operator=(const Neighberhood& other) = default;
    Vector<PizzaShop> &searchInKdtree(KDTree &tree);
    void searchInKdtree(Node *node, int depth);
    bool isInYRange(Node *node);
    bool isInXRange(Node *node);
    string get_name() const;
    // ~Neighberhood();
};

#endif
