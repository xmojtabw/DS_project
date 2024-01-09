#include "pizzashop.h"

PizzaShop::PizzaShop(int x, int y,
                     string n, bool is_m) : name(n),
                                            x_coordinate(x),
                                            y_coordinate(y),
                                            is_main_branch(is_m)
{
}

bool PizzaShop::operator==(const PizzaShop &other) const
{
    return (this->hasSamePoint(other) && this->name == other.name);
}

bool PizzaShop::hasSamePoint(const PizzaShop &other) const
{
    return (x_coordinate == other.x_coordinate && y_coordinate == other.y_coordinate);
}

int PizzaShop::getX() const
{
    return x_coordinate;
}

int PizzaShop::getY() const
{
    return y_coordinate;
}

string PizzaShop::getName() const
{
    return name;
}

bool PizzaShop::isMainBranch() const
{
    return is_main_branch;
}
