#ifndef _PIZZASHOP_H_
#define _PIZZASHOP_H_
#include <iostream>
using namespace std;
class PizzaShop
{
private:
    string name;
    int x_coordinate;
    int y_coordinate;
    bool is_main_branch;

public:
    PizzaShop() = default;
    PizzaShop(int x, int y, string n, bool is_m = true);
    PizzaShop(const PizzaShop &other) = default;
    PizzaShop &operator=(const PizzaShop &other) = default;
    bool operator==(const PizzaShop &other) const;
    bool hasSamePoint(const PizzaShop &other) const;
    int getX() const;
    int getY() const;
    string getName() const;
    bool isMainBranch() const;
};
#endif