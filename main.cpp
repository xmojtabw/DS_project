#include <iostream>
// #include "vectorT.h"

// #include "pizzashop.h"
// #include "heapsort.h"
#include "geometry.h"
// #include "kdtree.h"
#include "Hash.h"
#include "neighberhood.h"
#include <utility>
#include <sstream>
// #include "heapsort.h"

// if debug :
// #include "geometry.cpp"
// #include "pizzashop.cpp"
// #include "kdtree.cpp"
// #include "node.cpp"
// #include "neighborhood.cpp"
// #include "Hash.cpp"

using namespace std;

Vector<PizzaShop> myvec;
Vector<PizzaShop> main_brs;
Vector<Neighberhood> neighberhood;
KDTree kd;
Hash<Vector<node_t<Vector<PizzaShop>>>> hash_table;
Hash<PizzaShop> names;
Hash<Neighberhood> negs;

void input_handler(int itr);

class Commands
{
public:
    static Vector<pair<string, function<void(Vector<string> inputs)>>> command_vector;

    static void showCommands(Vector<string> inputs) {
        if(inputs.getSize() != 0) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            for(auto const& command : Commands::command_vector) {
                cout << command.first << endl;
            }
        }
    }

    static void addNeighberhood(Vector<string> inputs)
    {
        if(inputs.getSize() != 9) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            string name = inputs[0];
            inputs.popFront();
            int tmp = 0;
            Vector<int> x_coordinates, y_coordinates;
            for (int i = 0; i < inputs.getSize(); i++) {
                if (i % 2) {
                    tmp = stoi(inputs[i]);
                    y_coordinates.pushBack(tmp);
                } else {
                    tmp = stoi(inputs[i]);
                    x_coordinates.pushBack(tmp);
                }
            }
            heapSort<int>(x_coordinates);
            heapSort<int>(y_coordinates);
            Neighberhood n(name, x_coordinates[3], y_coordinates[0],
                           x_coordinates[0], y_coordinates[0],
                           x_coordinates[0], y_coordinates[3],
                           x_coordinates[3], y_coordinates[3]);
            neighberhood.pushBack(n);
            negs.insert(n);
        }
    }

    static void addPizzaShop(Vector<string> inputs)
    { // Input pattern : X_coordinate Y_coordinate Name
        if(inputs.getSize() != 3) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            int x, y;
            bool exist = false;
            bool name_exist = false;
            x = stoi(inputs[0]);
            y = stoi(inputs[1]);
            string name = inputs[2];
            PizzaShop psb(x, y, name);
            Node *shop_search = new Node(psb);
            PizzaShop name_search_result = names.search(psb);
            Node *tmp = nullptr;
            if (kd.getVec().getSize())
                tmp = kd.findNearestNeighbor(nullptr, kd.getRoot(), shop_search, 0);
            if (tmp) {
                exist = tmp->getValue().hasSamePoint(psb);
            }
            if (exist) {
                cerr << "Pizza shop with this coordinates has exist!" << endl;
            } else {
                if (name_search_result.getFind()) {
                    cerr << "Pizza shop with this name has exist already!" << endl;
                } else {
                    kd.insertToTree(psb);
                    names.insert(psb);
                    myvec.pushBack(psb);
                    main_brs.pushBack(psb);
                }

            }
        }
    }

    static void addBranch(Vector<string> inputs)
    {

        if(inputs.getSize() != 4) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            int x, y;
            bool exist = false;
            bool name_exist = false;
            x = stoi(inputs[0]);
            y = stoi(inputs[1]);
            string name = inputs[2];
            string main_br = inputs[3];
            PizzaShop psb(x, y, name, main_br);
            Node *shop_search = new Node(psb);
            PizzaShop name_search_result = names.search(psb);
            Node *tmp = nullptr;
//        kd.insertToTree(psb);

            if (kd.getVec().getSize())
                tmp = kd.findNearestNeighbor(nullptr, kd.getRoot(), shop_search, 0);
            if (tmp) {
                exist = tmp->getValue().hasSamePoint(psb);
            }
            if (exist) {
                cerr << "Pizza shop with this coordinates has exist!" << endl;
            } else {
                if (name_search_result.getFind()) {
                    cerr << "Pizza shop with this name has exist already!" << endl;
                } else {
                    kd.insertToTree(psb);
                    names.insert(psb);
                    myvec.pushBack(psb);
                    main_brs.pushBack(psb);
                }

            for (auto &brs: main_brs) {
                if (main_br == brs.getName()) {
                    brs.addBranch();
                    break;
                }
            }
        }
    }

    static void deleteBranch(Vector<string> inputs)
    {
        // Delete a branch of PizzaShop with x,y coordinates and name.
        if(inputs.getSize() != 2) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            if (kd.getVec().getSize() == 0) {
                cout << "KDTree is empty!" << endl;
                return;
            }
            int x, y;
            x = stoi(inputs[0]);
            y = stoi(inputs[1]);
            PizzaShop tmp(x, y, "tmp", false);
            Node *query = new Node(tmp);
            Node *find = kd.findNearestNeighbor(nullptr, kd.getRoot(), query, 0);
            if (find->getValue().hasSamePoint(tmp)) {
                if (find->getValue().isMainBranch())
                    cout << "Cannot remove this node!" << endl;
                else {
                    for (auto &shop: main_brs) {
                        if (shop.getName() == find->getValue().getMainBranchName())
                            shop.reduceBranch();
                    }
                    kd.removeFromTree(find);
                    myvec.erase(find->getValue());
            } 
          else 
          {
                cout << "This point doesn't exist!" << endl;
            }
        }

    }

    static void pizzaShopsNeighborhood(Vector<string> inputs)
    {
        // Prints all PizzaShops in a neighborhood with name of this neighborhood.
        if(inputs.getSize() != 1) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            Vector<PizzaShop> neighborhood_shops;
            string key = inputs[0];
//            for (auto &neighs: neighberhood) {
//                if (neighs.get_name() == key)
//                    neighborhood_shops = neighs.searchInKdtree(kd);
//            }
            if(key != negs.search(key).get_name()) {
                cerr << "Neighborhood not found!" << endl;
            }
//            if(neighborhood_shops.getSize() == 0) {
//                cerr << "Neighborhood not found!" << endl;
//            }
            else {
                if(kd.getVec().getSize() == 0) {
                    cout << "KDTree is empty!" << endl;
                }
                else {
                    neighborhood_shops = negs.search(key).searchInKdtree(kd);
                    if (neighborhood_shops.getSize() == 0) {
                        cerr << "Neighborhood not has any shop!" << endl;
                    }
                    for (auto &shops: neighborhood_shops) {
                        cout << shops;
                    }
                }
            }
        }
    }

    static void pizzaShopsBranches(Vector<string> inputs)
    {
        if(inputs.getSize() != 1) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            string key = inputs[0];
            Linkedlist<PizzaShop> branches = names.searchForList(key);
            node_t<PizzaShop> *tmp = branches.get_first();
            while (tmp) {
                if (tmp->get_key() == names.hash_string(key))
                    cout << tmp->get_value() << endl;
                tmp = tmp->get_next();
            }
        }
    }

    static void findNearest(Vector<string> inputs) {
        if(inputs.getSize() != 2) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            int x, y;
            x = stoi(inputs[0]);
            y = stoi(inputs[1]);
            PizzaShop tmp(x, y, "tmp");
            Node *query_point = new Node(tmp);
            Node *nearest = kd.findNearestNeighbor(nullptr, kd.getRoot(), query_point, 0);
            cout << nearest->getValue();
            nearest->getValue().isMainBranch() ? cout << " , Main branch" << endl : cout << " , Sub branch" << endl;
            delete (query_point);
        }
    }

    static void findNearestBranch(Vector<string> inputs)
    {
        if(inputs.getSize() != 3) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
            return;
        }
        int x, y;
        x = stoi(inputs[0]);
        y = stoi(inputs[1]);
        string key = inputs[2];
        Vector<PizzaShop> branch;
        for (int i = 0; i < myvec.getSize(); i++)
        {
            if (myvec[i].getMainBranchName() == key)
            {
                branch.pushBack(myvec[i]);
            }
        }
        KDTree branch_kdtree(branch);
        PizzaShop tmp(x, y, "tmp");
        Node *query_point = new Node(tmp);
        Node *nearest =
            branch_kdtree.findNearestNeighbor(nullptr, branch_kdtree.getRoot(), query_point, 0);
        cout << nearest->getValue();
        nearest->getValue().isMainBranch() ? cout << " , Main branch" : cout << " , Sub branch" << endl;
        delete (query_point);
        delete (nearest);
    }

    static void shopsInCircle(Vector<string> inputs)
    {
        if(inputs.getSize() != 3)
        {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            int x = stoi(inputs[0]);
            int y = stoi(inputs[1]);
            int r = stoi(inputs[2]);
            PizzaShop query(x,y,"query",false);
            Node* center= new Node(query);
            Vector<Node*> inArea;
            kd.findNearestNeighbor(nullptr,kd.getRoot(),center,0,r,inArea);
            for(auto const& nodes : inArea)
                cout << nodes->getValue() << endl;
        }
    }

    static void shopWithMostBranches(Vector<string> inputs)
    {
        // Prints PizzaShop which has most branches between all PizzaShops
        heapSort<PizzaShop>(main_brs);
        cout << main_brs[0];
    }

    static void undoCommand(Vector<string> inputs)
    {
        if(inputs.getSize() != 2) {
            cerr << "Command not found.for see commands enter Show_commands" << endl;
        }
        else {
            int time = stoi(inputs[0]);
            int command = stoi(inputs[1]);
            Vector<node_t<Vector<PizzaShop>>> tmp = hash_table.search1(time);
            if(command >= tmp.getSize()) {
                cerr << "This time doesn't exist!" << endl;
            }
            else {
                Vector<PizzaShop> tmp_vec = tmp[command].get_value();
                KDTree tmpkd(tmp_vec);
                string input;
                if(tmpkd.getVec().getSize() == 0) {
                    cerr << "KDTree is empty :)" << endl;
                    return;
                }
                while(true) {
                    cin >> input;
                    if(input == "Near-P") {
                        int x,y;
                        cin >> x >> y;
                        PizzaShop tmp(x,y,"tmp");
                        Node* query = new Node(tmp);
                        Node* result = tmpkd.findNearestNeighbor(nullptr,tmpkd.getRoot(),query,0);
                        cout << result->getValue();
                    }
                    else if(input == "List-P") {
                        string key;
                        Vector<PizzaShop> neighborhood_shops;
                        cin >> key;
                        if(key != negs.search(key).get_name()) {
                            cerr << "Neighborhood not found!" << endl;
                        }
                        else {
                            if(tmpkd.getVec().getSize() == 0) {
                                cout << "KDTree is empty!" << endl;
                            }
                            else {
                                neighborhood_shops = negs.search(key).searchInKdtree(tmpkd);
                                if (neighborhood_shops.getSize() == 0) {
                                    cerr << "Neighborhood not has any shop!" << endl;
                                }
                                for (auto &shops: neighborhood_shops) {
                                    cout << shops;
                                }
                            }
                        }

                    }
                    else if(input == "Avail-P") {
                        int x,y,r;
                        cin >> x >> y >> r;
                        PizzaShop query(x,y,"query",false);
                        Node* center= new Node(query);
                        Vector<Node*> inArea;
                        tmpkd.findNearestNeighbor(nullptr,tmpkd.getRoot(),center,0,r,inArea);
                        for(auto const& nodes : inArea)
                            cout << nodes->getValue() << endl;
                    }
                    else if(input == "Redo") {
                        break;
                    }
                }
            }
//            Vector<node_t<KDTree>> tmp = hash_table.search1(time);
//            cout << tmp[0].get_value().getRoot()->getValue();
        }
    }

    static void print(Vector<string>inputs)

    {
        kd.print();
    }
};

Vector<pair<string, function<void(Vector<string> inputs)>>> Commands::command_vector =
{
    {"Show_commands",Commands::showCommands},
    {"Add-N", Commands::addNeighberhood},
    {"Add-P", Commands::addPizzaShop},
    {"Add-Br", Commands::addBranch},
    {"Del-Br", Commands::deleteBranch},
    {"List-P", Commands::pizzaShopsNeighborhood},
    {"List-Brs", Commands::pizzaShopsBranches},
    {"Near-P", Commands::findNearest},
    {"Near-Br", Commands::findNearestBranch},
    {"Avail-P", Commands::shopsInCircle},
    {"Most-Brs", Commands::shopWithMostBranches},
    {"Undo", Commands::undoCommand},
    {"print",Commands::print}
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
    while (true)
    {
        input_handler(i++);
    }
}

void input_handler(int itr)
{
    node_t<Vector<PizzaShop>> tmp_vec (itr, nullptr,myvec);
    Vector<node_t<Vector<PizzaShop>>> time_vec;
    time_vec.pushBack((tmp_vec));
    hash_table.insert(itr, time_vec);
    string user_input;
    bool is_correct = false;
    bool flag = false;
    if (getline(cin, user_input))
    {
        istringstream user_input_stream(user_input);
        Vector<Vector<string>> split_input;
        string word;
        int i = 0;
        Vector<string> tmp;
        while (user_input_stream >> word)
        {
            if (word == "&&")
            {
                flag = true;
                split_input.pushBack(tmp);
                tmp = {};
                i++;
                continue;
            }
            if (word != "")
            {
                tmp.pushBack(word);
            }
        }
        split_input.pushBack(tmp);


        for (int j = 0, command_itr = 0; j < split_input.getSize(); j++)
        {
            for (int z = 0; z < Commands::command_vector.getSize(); z++)
            {
                if (Commands::command_vector[z].first == split_input[j][0])
                {
                    split_input[j].popFront();
                    if(command_itr) {
                    node_t<Vector<PizzaShop>> command_kd(command_itr, nullptr, myvec);
                    Vector<node_t<Vector<PizzaShop>>> tmp_vec;
                    tmp_vec.pushBack(command_kd);
                    hash_table.add(itr,command_itr,tmp_vec);
                    }

                    Commands::command_vector[z].second(split_input[j]);
                    is_correct = true;
                    command_itr++;
                    break;
                }
            }
        }
    }
    if (!is_correct)
        cout << "Command not found!" << endl;
}
