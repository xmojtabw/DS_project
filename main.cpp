#include <iostream>
// #include "vectorT.h"
// #include "pizzashop.h"
#include "geometry.h"
// #include "kdtree.h"
#include "Hash.h"
#include "neighberhood.h"
#include <utility>
#include <sstream>
//#include "heapsort.h"

// if debug :
// #include "geometry.cpp"
// #include "pizzashop.cpp"
// #include "kdtree.cpp"
// #include "node.cpp"
// #include "neighborhood.cpp"

using namespace std;

Vector<PizzaShop> myvec;
Vector<PizzaShop> main_brs;
Vector<Neighberhood> neighberhood;
KDTree kd;
Hash<Vector<node_t<KDTree>>> hash_table;
Hash<PizzaShop> names;


void input_handler(int itr);

class Commands {
public:
    static Vector<pair<string,function<void(Vector<string> inputs)>>> command_vector;

    static void addNeighberhood(Vector<string> inputs) {
        string name = inputs[0];
        inputs.popFront();
        int tmp = 0;
        Vector<int> x_coordinates,y_coordinates;
        for(int i = 0 ; i < inputs.getSize() ; i++) {
            if(i%2) {
                tmp = stoi(inputs[i]);
                y_coordinates.pushBack(tmp);
            }
            else {
                tmp = stoi(inputs[i]);
                x_coordinates.pushBack(tmp);
            }
        }
        heapSort<int>(x_coordinates);
        heapSort<int>(y_coordinates);
        Neighberhood n(name,x_coordinates[3],y_coordinates[0],
                            x_coordinates[0],y_coordinates[0],
                            x_coordinates[0],y_coordinates[3],
                            x_coordinates[3],y_coordinates[3]);
        neighberhood.pushBack(n);
    }

    static void addPizzaShop(Vector<string> inputs) {//Input pattern : X_coordinate Y_coordinate Name
        int x, y;
        x = stoi(inputs[0]);
        y = stoi(inputs[1]);
        string name = inputs[2];
        PizzaShop psb(x, y, name);
        names.insert(psb);
        myvec.pushBack(psb);
        main_brs.pushBack(psb);
    }

    static void addBranch(Vector<string> inputs) {
        int x, y;
        x = stoi(inputs[0]);
        y = stoi(inputs[1]);
        string name = inputs[2];
        string main_br = inputs[3];
        PizzaShop psb(x, y, name, main_br);
        myvec.pushBack(psb);
        names.insert(psb);
        for(auto &brs : main_brs) {
            if(main_br == brs.getName())
            {
                brs.addBranch();
                break;
            }
        }

    }

    static void deleteBranch(Vector<string> inputs) {
        //Delete a branch of PizzaShop with x,y coordinates and name.
    }

    static void pizzaShopsNeighberhood(Vector<string> inputs) {
        //Prints all PizzaShops in a neighborhood with name of this neighborhood.
        Vector<PizzaShop> neighborhood_shops;
        string key = inputs[0];
        for(auto &neighs : neighberhood) {
            if(neighs.get_name() == key)
                neighborhood_shops = neighs.searchInKdtree(kd);
        }
        for (auto &shops : neighborhood_shops) {
            cout << shops;
        }
    }

    static void pizzaShopsBranches(Vector<string> inputs) {
        string key = inputs[0];
        Linkedlist<PizzaShop> branches = names.searchForList(key);
        node_t<PizzaShop>* tmp = branches.get_first();
        while(tmp) {
            if(tmp->get_key() == names.hash_string(key))
                cout << tmp->get_value() << endl;
            tmp = tmp->get_next();
        }
    }

    static void findNearest(Vector<string> inputs) {
        int x, y;
        x = stoi(inputs[0]);
        y = stoi(inputs[1]);
        PizzaShop tmp(x, y, "tmp");
        Node *query_point = new Node(tmp);
        Node *nearest = kd.findNearestNeighbor(nullptr, kd.getRoot(), query_point, 0);
        cout << nearest->getValue();
        nearest->getValue().isMainBranch() ? cout << "Main branch" : cout << "Sub branch" << endl;
        delete(query_point);
    }

    static void findNearestBranch(Vector<string> inputs) {

        int x, y;
        x = stoi(inputs[0]);
        y = stoi(inputs[1]);
        string key = inputs[2];
        Vector<PizzaShop> branch;
        for (int i = 0; i < myvec.getSize(); i++)
        {
            if (myvec[i].getName() == key)
            {
                branch.pushBack(myvec[i]);
            }
        }
        KDTree branch_kdtree(branch);
        PizzaShop tmp(x, y, "tmp");
        Node *query_point = new Node(tmp);
        Node *nearest =
                branch_kdtree.findNearestNeighbor(nullptr,branch_kdtree.getRoot(), query_point, 0);
        cout << nearest->getValue();
        nearest->getValue().isMainBranch() ? cout << "Main branch" : cout << "Sub branch" << endl;
        delete(query_point);
        delete(nearest);
    }

    static void shopsInCircle(Vector<string> inputs) {

    }

    static void shopWithMostBranches(Vector<string> inputs) {
        // Prints PizzaShop which has most branches between all PizzaShops
        heapSort<PizzaShop>(main_brs);
        cout << main_brs[0];
    }

    static void undoCommand(Vector<string> inputs) {

    }
};


Vector<pair<string,function<void(Vector<string> inputs)>>> Commands::command_vector =
{
        {"Add-N",Commands::addNeighberhood},
        {"Add-P", Commands::addPizzaShop},
        {"Add-Br", Commands::addBranch},
        {"Del-Br", Commands::deleteBranch},
        {"List-P", Commands::pizzaShopsNeighberhood},
        {"List-Brs", Commands::pizzaShopsBranches},
        {"Near-P", Commands::findNearest},
        {"Near-Br", Commands::findNearestBranch},
        {"Avail-P",Commands::shopsInCircle},
        {"Most-Brs", Commands::shopWithMostBranches},
        {"Undo", Commands::undoCommand}
};


int main()
{

//    PizzaShop ps1(1, 11, "a");
//    PizzaShop ps2(8, 12, "b");
//    PizzaShop ps3(5, 8, "c");
//    PizzaShop ps4(4, 1, "d");
//    PizzaShop ps5(8, 3, "e");
//    PizzaShop ps6(10, 9, "f");
//    PizzaShop ps7(11, 5, "g");
//    PizzaShop ps8(12, 1, "h");
//    PizzaShop ps9(1000, 100, "i");
//    myvec.pushBack(ps1);
//    myvec.pushBack(ps2);
//    myvec.pushBack(ps3);
//    myvec.pushBack(ps4);
//    myvec.pushBack(ps5);
//    myvec.pushBack(ps6);
//    myvec.pushBack(ps7);
//    myvec.pushBack(ps8);
//    myvec.pushBack(ps9);
//    KDTree kd1(myvec);
//          for (int i = 0; i < myvec.getSize(); i++)
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
//     Vector<PizzaShop> another = kd.getVec();
//     for (int i = 0; i < another.getSize(); i++)
//     {
//         cout << another[i].getX() << " " << another[i].getY() << " " << another[i].getName() << endl;
//     }
//    PizzaShop p(9, 2, "a");
//    Node *point = new Node(p);
//    Node *best_res = kd1.findNearestNeighbor(nullptr, kd1.getRoot(), point, 0);
//    cout << "out put is " << endl;
//    kd.print(4);
/********************************Old Main***************************/
//    while (1)
//    {
//        string command;
//        cin >> command;
//        if (command == "Add-N")
//        { // Add neighborhood
//        }
//        else if (command == "Add-P")
//        { // Add "PizzaShop" which is main branch.
//            int x, y;
//            string name;
//            cin >> x >> y >> name;
//            PizzaShop psb(x, y, name);
//            myvec.pushBack(psb);
//            main_brs.pushBack(psb);
//        }
//        else if (command == "Add-Br")
//        { // Add a branch of a PizzaShop.
//            int x, y;
//            string name, main_br;
//            cin >> x >> y >> name >> main_br;
//            PizzaShop psb(x, y, name, main_br);
//            myvec.pushBack(psb);
//            for (int i = 0; i < main_brs.getSize(); i++)
//            {
//                if (main_brs[i].getName() == main_br)
//                {
//                    main_brs[i].addBranch();
//                }
//            }
//        }
//        else if (command == "Del-Br")
//        { // Delete a branch of PizzaShop with x,y coordinates and name.
//        }
//        else if (command == "List-P")
//        { // Prints all PizzaShops in a neighborhood with name of this neighborhood.
//        }
//        else if (command == "List-Brs")
//        { // Prints coordinates of all branch of a PizzaShop which user pass the name of it.
//            string key;
//            cin >> key;
//            for (int i = 0; i < myvec.getSize(); i++)
//            {
//                if (myvec[i].getMainBranchName() == key)
//                {
//                    cout << "Branch " << i << ':' << myvec[i].getX() << ',' << myvec[i].getY() << endl;
//                }
//            }
//        }
//        else if (command == "Near-P")
//        { // Prints nearest PizzaShop to the coordinates which user enter.
//            int x, y;
//            cin >> x >> y;
//            PizzaShop tmp(x, y, "tmp");
//            Node *query_point = new Node(tmp);
//            Node *nearest = kd.findNearestNeighbor(nullptr, kd.getRoot(), query_point, 0);
//            cout << nearest->getValue().getName() << ':' << nearest->getValue().getX() << ',' << nearest->getValue().getY();
//            nearest->getValue().isMainBranch() ? cout << "Main branch" : cout << "Sub branch" << endl;
//        }
//        else if (command == "Near-Br")
//        { // Same as Near-P but prints nearest branch of PizzaShop which user choose it.
//            string key;
//            int x, y;
//            cin >> key >> x >> y;
//            Vector<PizzaShop> branch;
//            for (int i = 0; i < myvec.getSize(); i++)
//            {
//                if (myvec[i].getName() == key)
//                {
//                    branch.pushBack(myvec[i]);
//                }
//            }
//            KDTree branch_kdtree(branch);
//            PizzaShop tmp(x, y, "tmp");
//            Node *query_point = new Node(tmp);
//            Node *nearest =
//                branch_kdtree.findNearestNeighbor(nullptr, branch_kdtree.getRoot(), query_point, 0);
//            cout << nearest->getValue().getName() << ':' << nearest->getValue().getX() << ',' << nearest->getValue().getY();
//            nearest->getValue().isMainBranch() ? cout << "Main branch" : cout << "Sub branch" << endl;
//        }
//        else if (command == "Avail-P")
//        {
//        }
//        else if (command == "Most-Brs")
//        { // Prints PizzaShop which has most branches between all PizzaShops.
//        }
//        else if (command == "Exit")
//        {
//            break;
//        }
//    }
/*******************************************************/
//    Neighberhood n("first", 4, 10, 8, 10, 8, 2, 4, 2);
//    Vector<PizzaShop> t = n.searchInKdtree(kd);
//    for (int i = 0; i < t.getSize(); i++)
//    {
//        cout << t[i].getName() << " (" << t[i].getX() << "," << t[i].getY() << ")" << endl;
//    }
    int i = 0;
    while(true) {
        input_handler(i++);
    }
}

void input_handler(int itr) {
    node_t<KDTree>* time_kd = new node_t<KDTree>(itr, nullptr,kd);
    Vector<node_t<KDTree>> time_vec(100);
    time_vec.pushBack((*time_kd));
    hash_table.insert(itr,time_vec);
    string user_input;
    bool is_correct = false;
    bool flag = false;
    if(getline(cin, user_input)) {
        istringstream user_input_stream(user_input);
        Vector<Vector<string>> split_input;
        string word;
        int i = 0;
        Vector<string> tmp;
        while(user_input_stream >> word) {
            if(word == "&&")
            {
                flag = true;
                split_input.pushBack(tmp);
                tmp = {};
                i++;
                continue;
            }
            if (word != "") {
                tmp.pushBack(word);
            }
        }
        if(!flag) {
            split_input.pushBack(tmp);
        }

        for(int j = 0 ; j < split_input.getSize() ; j++) {
            for(int z = 0, command_itr = 0 ; z < Commands::command_vector.getSize() ; z++) {
                if(Commands::command_vector[z].first == split_input[j][0]) {
                    split_input[j].popFront();
                    node_t<KDTree> command_kd(command_itr, nullptr,kd);
                    hash_table.search1(itr).pushBack(command_kd);
                    Commands::command_vector[z].second(split_input[j]);
                    is_correct = true;
                    command_itr++;
                    break;
                }
            }
        }
    }
    if(!is_correct)
        cout << "Command not found!" << endl ;
}
