#include <iostream>
// #include "vectorT.h"
// #include "pizzashop.h"
#include "geometry.h"
// #include "heapsort.h"
// #include "kdtree.h"
#include "neighberhood.h"

// if debug :
// #include "geometry.cpp"
// #include "pizzashop.cpp"
// #include "kdtree.cpp"
// #include "node.cpp"
// #include "neighborhood.cpp"

using namespace std;
int main()
{
    Vector<PizzaShop> myvec;
    PizzaShop ps1(1, 11, "a");
    PizzaShop ps2(8, 12, "b");
    PizzaShop ps3(5, 8, "c");
    PizzaShop ps4(4, 1, "d");
    PizzaShop ps5(8, 3, "e");
    PizzaShop ps6(8, 9, "f");
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

    Neighberhood n("first", 4, 10, 8, 10, 8, 2, 4, 2);
    Vector<PizzaShop> t = n.searchInKdtree(kd);
    for (int i = 0; i < t.getSize(); i++)
    {
        cout << t[i].getName() << " (" << t[i].getX() << "," << t[i].getY() << ")" << endl;
    }
}