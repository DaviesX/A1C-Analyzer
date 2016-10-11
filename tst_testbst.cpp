#include <iostream>
#include "tst_testbst.h"
#include "bst.h"


void test_bst()
{
        BST<int> bst;
        bst.insert(1);
        bst.insert(3);
        bst.insert(2);
        bst.insert(4);

        std::cout << bst << std::endl;

        std::cout << *bst.find(1) << std::endl;
        std::cout << bst.find(100) << std::endl;

        bst.remove(3);
        std::cout << bst.find(3) << std::endl;

        std::cout << bst << std::endl;
}
