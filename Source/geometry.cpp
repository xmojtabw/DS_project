#include "geometry.h"
double distance(const PizzaShop &one, const PizzaShop &other)
{
    return sqrt(
        ((one.getX() - other.getX()) * (one.getX() - other.getX())) +
        ((one.getY() - other.getY()) * (one.getY() - other.getY())));
}

double horizontalDistance(const PizzaShop &one, const PizzaShop &other)
{
    return abs(one.getX() - other.getX());
}

double verticalDistance(const PizzaShop &one, const PizzaShop &other)
{
    return abs(one.getY() - other.getY());
}

bool isInRange(const PizzaShop &one, const PizzaShop &other, const double &range)
{
    return distance(one, other) <= range;
}
