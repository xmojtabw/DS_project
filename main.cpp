#include <iostream>
#include "vectorT.h"
#include "pizzashop.h"
using namespace std;
int main()
{
    Vector<PizzaShop> myvec;
    PizzaShop ps(3, 2, "first shop");
    myvec.pushBack(ps);

    for (int i = 0; i < 1; i++)
    {
        cout << myvec[i].getName();
    }
}