#include <iostream>
#include "tst_testbst.h"
#include "bst.h"
#include <ctime>

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


void test_bst_speed()
{
        std::clock_t i_start;
        std::clock_t i_end;
        std::clock_t f_start;
        std::clock_t f_end;

        double duration;
        i_start = std::clock();

        BST<int> bst;
        int i = 0;
        while (i < 80000) {
                bst.insert(i);
                i++;
        }
        i_end =  std::clock();
        duration = ( i_end - i_start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"Insertion: "<< duration <<'\n';


        f_start = std::clock();
        int j = 0;
        while (j <80000) {
                bst.find(j);
                j++;
        }
        f_end = std::clock();
        duration = (f_end - f_start ) / (double) CLOCKS_PER_SEC;
        std::cout<<"Search: "<< duration <<'\n';


//        r_start = std::clock();
//        int k = 0;
//        while (k < 100000) {
//                bst.remove(k);
//                k++;
//        }
//        r_end = std::clock();
//        duration = (r_end - r_start ) / (double) CLOCKS_PER_SEC;
//        std::cout<<"Removal: "<< duration <<'\n';




}

