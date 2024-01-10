#include <iostream>
#include "vectorT.h"
#include "pizzashop.h"
#include "geometry.h"
// #include "heapsort.h"
#include "kdtree.h"

// if debug :
// #include "geometry.cpp"
// #include "pizzashop.cpp"
// #include "kdtree.cpp"
// #include "node.cpp"

using namespace std;
int main()
{
    Vector<PizzaShop> myvec;
    PizzaShop ps1(1, 11, "a");
    PizzaShop ps2(2, 9, "b");
    PizzaShop ps3(5, 8, "c");
    PizzaShop ps4(4, 2, "d");
    PizzaShop ps5(8, 3, "e");
    PizzaShop ps6(10, 10, "f");
    PizzaShop ps7(11, 5, "g");
    PizzaShop ps8(12, 1, "h");
    PizzaShop ps9(1000, 100, "i");
    myvec.pushBack(ps1);
    myvec.pushBack(ps2);
    myvec.pushBack(ps3);
    myvec.pushBack(ps4);
    myvec.pushBack(ps5);
    myvec.pushBack(ps6);
    myvec.pushBack(ps7);
    myvec.pushBack(ps8);
    myvec.pushBack(ps9);

    // for (int i = 0; i < myvec.getSize(); i++)
    // {
    //     cout << myvec[i].getName() << endl;
    // }

    // double d = distance(ps1, ps2);
    // cout << d << endl;
    // cout << isInRange(ps1, ps2, 9.6) << endl;

    // heapSort<PizzaShop>(myvec, 1, 4,
    //                     [](PizzaShop &one, PizzaShop &other) -> bool
    //                     { return one.getX() > other.getX(); });
    // for (int i = 0; i < myvec.getSize(); i++)
    // {
    //     cout << myvec[i].getX() << " " << myvec[i].getName() << endl;
    // }
    KDTree kd(myvec);
    // Vector<PizzaShop> another = kd.getVec();
    // for (int i = 0; i < another.getSize(); i++)
    // {
    //     cout << another[i].getX() << " " << another[i].getY() << " " << another[i].getName() << endl;
    // }
    cout << "out put is " << endl;
    kd.print(4);
}