#ifndef _PIZZASHOP_H_
#define _PIZZASHOP_H_
#include <iostream>
using namespace std;
class PizzaShop
{
private:
    string name;
    string main_branch;
    int x_coordinate;
    int y_coordinate;
    bool is_main_branch;
    int branches;

public:
    PizzaShop() = default;
    PizzaShop(int x, int y, string n, bool is_m = true);
    PizzaShop(int x, int y, string n,string b_n);//For sub-branch.
    PizzaShop(const PizzaShop &other) = default;
    PizzaShop &operator=(const PizzaShop &other) = default;
    bool operator==(const PizzaShop &other) const;
    bool operator<(const PizzaShop &other) const;
    friend std::ostream& operator<<(std::ostream& os, const PizzaShop& obj);
    int operator[](int axis);
    bool hasSamePoint(const PizzaShop &other) const;
    int getX() const;
    int getY() const;
    string getName() const;
    string getMainBranchName() const;
    const int branches_number() const;
    bool isMainBranch() const;
    void addBranch();
};
#endif