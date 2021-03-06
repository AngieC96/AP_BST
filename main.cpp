#include <iostream>
#include <memory>
#include <utility>
#include <vector>

/* In order to print a vector via 'cout << v' */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    auto itStop = v.cend();
    for (auto it = v.cbegin(); it != itStop; ++it) {
        os << *it;
        if (it != itStop - 1) os << ", ";
    }
    os << "]";
    return os;
}

#include "BST.hpp"
#include "Iterator.hpp"
#include "Node.hpp"

int main() {

    std::cout << "NODE CREATION TESTS" << std::endl << std::endl;

    std::cout << "Create empty Node with default constructor via `Node c`" << std::endl;
    APutils::Node<std::pair<int, int>> c;
    std::cout << "Create empty Node with default constructor via `Node c{}`" << std::endl;
    APutils::Node<std::pair<int,int>> c2{};
    
    std::cout << "Create Node with `int` Data" << std::endl;
    std::pair<int, int> testPair(3, 4);
    APutils::Node<std::pair<int,int>> testNode(testPair, nullptr);
    testNode.printNode();

    std::cout << "Create Node with `string : int` Data" << std::endl;
    std::pair<std::string, int> testPair2("Angela", 24);
    APutils::Node<std::pair<std::string,int>> testNode2(testPair2, nullptr);
    testNode2.printNode();
    
    std::cout << "Link Nodes:\nCreate Node with Data and Parent" << std::endl;
    APutils::Node<std::pair<int, int>> testNode3{testPair, &c};
    testNode3.printNode();

    //testNode2 = testNode;  // already NOT ALLOWED by the unique_ptr

    std::cout << "Create Node with Data, Parent and Children" << std::endl;
    std::pair<int, int> rootPair(1,1);
    std::pair<const int, int> leftPair(0,0);
    const std::pair<const int, int> rightPair(2,2);
    APutils::Node<std::pair<int, int>> nodeRoot(rootPair, nullptr);
    nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(leftPair, &nodeRoot));
    nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(rightPair, &nodeRoot));

    nodeRoot.printNode();
    nodeRoot.left->printNode();
    nodeRoot.right->printNode();


    std::cout << std::endl << "ITERATORS TESTS:" << std::endl;

    APutils::__iterator<APutils::Node<std::pair<int, int>>,std::pair<int, int>> it(&nodeRoot);
    
    std::cout << "Value: " << it->second << std::endl;
    it->second = 66;   /* Changing the `Value` of a `Node` through an iterator */
    std::cout << "Value: " << it->second << std::endl;

    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (*(it++)).first << std::endl;
    
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (*(it)).first << std::endl << std::endl;

    APutils::__iterator<APutils::Node<std::pair<int, int>>,std::pair<int, int>> it2(&nodeRoot);
    
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << (++it2)->first << std::endl;
    
    std::cout << "[" << &(*it) << "]    ";
    std::cout << "Key: " << it2->first << std::endl;


    std::cout << std::endl << "INSERT TESTS" << std::endl;

    APbst::bst<int, int> tree{};
    
    auto insroot = tree.insert(rootPair);
    std::cout << "Insert root: " << (insroot.second ? "OK" : "FAILED") << std::endl;
    
    auto insleft = tree.insert(leftPair);
    std::cout << "Insert left: " << (insleft.second ? "OK" : "FAILED") << std::endl;
    
    auto insright = tree.insert(rightPair);
    std::cout << "Insert right: " << (insright.second ? "OK" : "FAILED") << std::endl;
    
    auto ins3 = tree.insert(std::pair<int, int>(3,3));
    std::cout << "Insert 3: " << (ins3.second ? "OK" : "FAILED") << std::endl;
    
    auto ins5 = tree.insert(std::pair<int, int>(5,5));
    std::cout << "Insert 5: " << (ins5.second ? "OK" : "FAILED") << std::endl;
    
    auto ins6 = tree.insert(std::pair<const int, int>(6,6));
    std::cout << "Insert 6: " << (ins6.second ? "OK" : "FAILED") << std::endl;
    
    auto ins8 = tree.insert(std::pair<const int, int>(8,8));
    std::cout << "Insert 8: " << (ins8.second ? "OK" : "FAILED") << std::endl;
    
    auto ins8_2 = tree.insert(std::pair<const int, int>(8,8));
    std::cout << "Insert 8: " << (ins8_2.second ? "OK" : "FAILED") << std::endl;
    
    auto ins4 = tree.insert({4, 4});
    std::cout << "Insert 4: " << (ins4.second ? "OK" : "FAILED") << std::endl;


    std::cout << std::endl << "EMPLACE TESTS" << std::endl;

    auto empl7 = tree.emplace(7, 7);
    std::cout << "Emplacing 7: " << (empl7.second ? "OK" : "FAILED") << std::endl;

    auto empl11 = tree.emplace(11, 11);
    std::cout << "Emplacing 11: " << (empl11.second ? "OK" : "FAILED") << std::endl;

    auto empl11_2 = tree.emplace(11, 11);
    std::cout << "Emplacing 11: " << (empl11_2.second ? "OK" : "FAILED") << std::endl;


    std::cout << std::endl << "ITERATION TESTS" << std::endl;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << "[" << &(*it) << "]    ";
        std::cout << "Key: " << it->first << std::endl;
    }

    std::cout << std::endl;

    for (APbst::bst<int,int>::const_iterator it = tree.cbegin(); it != tree.cend(); ++it) {
        std::cout << "[" << &(*it) << "]    ";
        std::cout << "Key: " << it->first << std::endl;
    }

    std::cout << std::endl;
    
    /* C++-11 loop.
     * Use the following:
     *   - 'const auto& it' to observe the elements by const reference.
     *   - 'auto it'        to observe the elements by copying them (if copy is cheap).
     *   - 'auto& it'       to modify the elements in place by non-const reference.
     *   - 'auto&& it'      to modify the elements by proxy iterators, which are not
     *                      implemented in our case, so it works the same way as
     *                      'auto& it'.
     * Since 'it' is not a pointer in any of the above cases, there's no need to
     * dereference `it` (it's directly of type T of Node<T>).
     */
    for (const auto& it : tree) {
        std::cout << "[" << &(it) << "]    ";
        std::cout << "Key: " << it.first << std::endl;
    }

    std::cout << std::endl << "SUBSCRIPTING OPERATOR [] TESTS" << std::endl;

    // move:
    tree[1] = 11;  // update an existing value: calls the MOVE_INSERT since it creates a new pair using (1, 11) with the pair move constructor
    tree[10] = 10;  // insert a new value
    tree[9] = 9;  // insert a new value
    
    //copy:
    const int i = 2;
    tree[i] = 22;  // update an existing value: calls the MOVE_INSERT since it creates a new pair using (i, 22) with the pair copy constructor
    const int j = 12;
    tree[j] = 12;  // insert a new value
    
    tree[4] = tree[5];


    std::cout << std::endl << "PRINT TEST" << std::endl;

    std::cout << tree << std::endl;


    std::cout << std::endl << "FIND TESTS" << std::endl;

    /* Show that we can recast the tree as a const tree and then store the
     * iterator in a const_iterator type.
     */
    APbst::bst<int,int>::const_iterator it_1 = ((const APbst::bst<int,int>)tree).find(5);
    //it_1->second = 78;  // NOT allowed
    std::cout << ((it_1 == tree.cend()) ? "Key NOT found" : "Key found") << std::endl;

    auto it_2 = tree.find(6);
    it_2->second = 78;  // ALLOWED
    std::cout << ((it_2 == tree.end()) ? "Key NOT found" : "Key found") << std::endl;

    auto it_3 = tree.find(55);
    std::cout << ((it_3 == tree.end()) ? "Key NOT found" : "Key found") << std::endl;

    tree.find(5)->second = 78;
    std::cout << tree[5] << std::endl;

    const APbst::bst<int,int> const_tree{tree};
    auto it_const_1 = const_tree.find(1);  /* Calling the const version of find! */
    std::cout << ((it_const_1 == const_tree.end()) ? "Key NOT found" : "Key found") << std::endl;


    std::cout << std::endl << "ERASE TESTS" << std::endl;

    APbst::bst<int, int> treeAP{};
    treeAP.emplace(8,8);
    treeAP.emplace(3,3);
    treeAP.emplace(10,10);
    treeAP.emplace(1,1);
    treeAP.emplace(6,6);
    treeAP.emplace(4,4);
    treeAP.emplace(7,7);
    treeAP.emplace(14,14);
    treeAP.emplace(13,13);
    std::cout << "Before erasing: " << std::endl;
    std::cout << treeAP << std::endl;
    treeAP.erase(4);
    std::cout << "After erasing 4 (is leaf): " << std::endl;
    std::cout << treeAP << std::endl;
    treeAP.erase(10);
    std::cout << "After erasing 10 (has 14 as right child, which has 13 as left child): " << std::endl;
    std::cout << treeAP << std::endl;


    APbst::bst<int, int> treeAP2{};
    treeAP2.emplace(8,8);
    treeAP2.emplace(3,3);
    treeAP2.emplace(10,10);
    treeAP2.emplace(1,1);
    //treeAP2.emplace(6,6);
    treeAP2.emplace(4,4);
    treeAP2.emplace(7,7);
    treeAP2.emplace(14,14);
    treeAP2.emplace(13,13);
    treeAP2.emplace(5,5);
    treeAP2.erase(3);
    std::cout << "After erasing 3 (has a full subtree): " << std::endl;
    std::cout << treeAP2 << std::endl;

    APbst::bst<int, int> treeAP3{};
    treeAP3.emplace(8,8);
    treeAP3.emplace(3,3);
    treeAP3.emplace(10,10);
    treeAP3.emplace(1,1);
    treeAP3.emplace(6,6);
    treeAP3.emplace(4,4);
    treeAP3.emplace(7,7);
    treeAP3.emplace(14,14);
    treeAP3.emplace(13,13);
    treeAP3.emplace(5,5);
    treeAP3.emplace(9,9);
    treeAP3.erase(8);
    std::cout << "After erasing 8 (the root): " << std::endl;
    std::cout << treeAP3 << std::endl;


    APbst::bst<int, int> treeAPS{};
    treeAPS.emplace(8,8);
    treeAPS.emplace(3,3);
    treeAPS.emplace(1,1);
    treeAPS.emplace(6,6);
    treeAPS.emplace(4,4);
    treeAPS.emplace(5,5);
    std::cout << treeAPS << std::endl;
    treeAPS.erase(3);
    std::cout << "After erasing 3: " << std::endl;
    std::cout << treeAPS << std::endl;


    std::cout << std::endl << "MATCHING TESTS" << std::endl;

    std::stringstream ssAP3{};
    treeAP3.printRawTree(ssAP3);
    std::stringstream ssAP3_exp{};
    ssAP3_exp << "1 : 1\n3 : 3\n4 : 4\n5 : 5\n6 : 6\n7 : 7\n9 : 9\n10 : 10\n13 : 13\n14 : 14\n";
//    std::cout << ssAP3.str() << std::endl;
//    std::cout << ssAP3_exp.str() << std::endl;
    std::cout << ( (ssAP3.str() == ssAP3_exp.str()) ? "MATCH OK" : "MATCH FAIL") << std::endl;


    std::cout << std::endl << "BALANCE TEST" << std::endl;

    treeAP3.balance();
    std::cout << treeAP3 << std::endl;


    std::cout << std::endl << "COPY TESTS" << std::endl;
    APbst::bst<int, int> treeAP4{};
    treeAP4 = treeAP3;
    std::cout << treeAP4 << std::endl;

    APbst::bst<int, int> treeAP5{treeAP3};
    std::cout << treeAP5 << std::endl;


    std::cout << std::endl << "CLEAR TEST" << std::endl;

    tree.clear();

    for (const auto& it : tree) {
        std::cout << "[" << &(it) << "]    ";
        std::cout << "Key: " << it.first << std::endl;
    }
    std::cout << "Finished printing" << std::endl;



    std::cout << std::endl << "PLAYER STATS BST TESTS" << std::endl;
    APbst::bst<std::string, std::vector<double>> playerStats{};
    //playerStats.insert(std::pair<const std::string,std::vector<double>>("Bruce Lee",std::vector<double>{170,70,47}));
    //playerStats.insert({"Bruce Lee",std::vector<double>{170,70,47}});
    playerStats.emplace("Bruce Lee",std::vector<double>{170,70,47});
    playerStats.emplace("Michael Jackson",std::vector<double>{210,90,50});
    playerStats.emplace("Arnold Schwarznegger",std::vector<double>{190,80,60});
    std::cout << playerStats << std::endl;


    return 0;
}
