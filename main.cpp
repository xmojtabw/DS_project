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
    Vector<PizzaShop> main_brs;
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
    PizzaShop p(3, 5, "a");
    Node *point = new Node(p);
    Node* best_res = kd.findNearestNeighbor(nullptr,kd.getRoot(),point,0);
    cout << "out put is " << endl;
    kd.print(4);


    while(1) {
         string command;
         cin >> command;
         if(command == "Add-N"){//Add neighborhood

         }
         else if(command == "Add-P") {//Add "PizzaShop" which is main branch.
            int x,y;
            string name;
            cin >> x >> y >> name;
            PizzaShop psb(x,y,name);
            myvec.pushBack(psb);
            main_brs.pushBack(psb);
         }
         else if(command == "Add-Br") {//Add a branch of a PizzaShop.
             int x,y;
             string name, main_br;
             cin >> x >> y >> name >> main_br;
             PizzaShop psb(x,y,name, main_br);
             myvec.pushBack(psb);
             for(int i = 0 ; i < main_brs.getSize() ; i++) {
                 if(main_brs[i].getName() == main_br) {
                     main_brs[i].addBranch();
                 }
             }
         }
         else if(command == "Del-Br") {//Delete a branch of PizzaShop with x,y coordinates and name.

         }
         else if(command == "List-P") {//Prints all PizzaShops in a neighborhood with name of this neighborhood.

         }
         else if(command == "List-Brs") {//Prints coordinates of all branch of a PizzaShop which user pass the name of it.
            string key;
            cin >> key;
            for(int i = 0 ; i < myvec.getSize() ; i++) {
                if(myvec[i].getName() == key) {
                    cout << "Branch " << i << ':' << myvec[i].getX() << ',' << myvec[i].getY() << endl;
                }
            }
         }
         else if(command == "Near-P") {//Prints nearest PizzaShop to the coordinates which user enter.
            int x,y;
            cin >> x >> y;
            PizzaShop tmp(x, y, "tmp");
            Node *query_point = new Node(tmp);
            Node* nearest = kd.findNearestNeighbor(nullptr,kd.getRoot(),query_point,0);
            cout << nearest->getValue().getName() << ':' <<
            nearest->getValue().getX() << ',' << nearest->getValue().getY();
            nearest->getValue().isMainBranch() ? cout << "Main branch" : cout << "Sub branch" << endl;
         }
         else if(command == "Near-Br") {//Same as Near-P but prints nearest branch of PizzaShop which user choose it.
             string key;
             int x,y;
             cin >> key >> x >> y;;
             Vector<PizzaShop> branch;
             for(int i = 0 ; i < myvec.getSize() ; i++) {
                 if(myvec[i].getName() == key) {
                     branch.pushBack(myvec[i]);
                 }
             }
             KDTree branch_kdtree(branch);
             PizzaShop tmp(x, y, "tmp");
             Node *query_point = new Node(tmp);
             Node* nearest =
             branch_kdtree.findNearestNeighbor(nullptr,branch_kdtree.getRoot(),query_point,0);
             cout << nearest->getValue().getName() << ':' <<
             nearest->getValue().getX() << ',' << nearest->getValue().getY();
             nearest->getValue().isMainBranch() ? cout << "Main branch" : cout << "Sub branch" << endl;
         }
         else if(command == "Avail-P") {

         }
         else if(command == "Most-Brs") {//Prints PizzaShop which has most branches between all PizzaShops.

         }
         else if(command == "Exit") {
             break;
         }
     }

}