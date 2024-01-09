#include <iostream>
#include "vectorT.h"
#include "pizzashop.h"
#include "geometry.h"
using namespace std;
int main()
{
    Vector<PizzaShop> myvec;
    PizzaShop ps1(-3, -4, "first shop");
    PizzaShop ps2(3, 4, "second shop");
    myvec.pushBack(ps1);
    myvec.pushBack(ps2);

    for (int i = 0; i < myvec.getSize(); i++)
    {
        cout << myvec[i].getName() << endl;
    }

    double d = distance(ps1, ps2);
    cout << d << endl;
    cout << isInRange(ps1, ps2, 9.6);
}