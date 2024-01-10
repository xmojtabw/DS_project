#include <iostream>
#include "vectorT.h"
#include "pizzashop.h"
#include "geometry.h"
#include "heapsort.h"

// // if debug :
// #include "geometry.cpp"
// #include "pizzashop.cpp"

using namespace std;
int main()
{
    Vector<PizzaShop> myvec;
    PizzaShop ps1(-3, -4, "first shop");
    PizzaShop ps2(1, 4, "second shop");
    PizzaShop ps3(5, 4, "third shop");
    PizzaShop ps4(2, 4, "4 shop");
    PizzaShop ps5(9, 4, "5 shop");
    PizzaShop ps6(0, 4, "6 shop");
    myvec.pushBack(ps1);
    myvec.pushBack(ps2);
    myvec.pushBack(ps3);
    myvec.pushBack(ps4);
    myvec.pushBack(ps5);
    myvec.pushBack(ps6);

    // for (int i = 0; i < myvec.getSize(); i++)
    // {
    //     cout << myvec[i].getName() << endl;
    // }

    // double d = distance(ps1, ps2);
    // cout << d << endl;
    // cout << isInRange(ps1, ps2, 9.6) << endl;

    heapSort<PizzaShop>(myvec, 1, 4,
                        [](PizzaShop &one, PizzaShop &other) -> bool
                        { return one.getX() > other.getX(); });
    for (int i = 0; i < myvec.getSize(); i++)
    {
        cout << myvec[i].getX() << " " << myvec[i].getName() << endl;
    }
}