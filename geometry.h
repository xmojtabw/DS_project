#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "pizzashop.h"
#include "math.h"
double distance(const PizzaShop &one, const PizzaShop &other);
double horizontalDistance(const PizzaShop &one, const PizzaShop &other);
double verticalDistance(const PizzaShop &one, const PizzaShop &other);
bool isInRange(const PizzaShop &one, const PizzaShop &other, const double &range);
#endif