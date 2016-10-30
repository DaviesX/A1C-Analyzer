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


template <typename T>
static void shuffle(std::vector<T>& objs)
{
        const int n = objs.size();
        for (int i = 1; i < n; i ++) {
                int r = rand()/(float) RAND_MAX * i;
                T tmp = objs[i];
                objs[i] = objs[r];
                objs[r] = tmp;
        }
}

void test_bst_speed()
{
        std::clock_t i_start;
        std::clock_t i_end;
        std::clock_t f_start;
        std::clock_t f_end;
        const int n = 80000;

        double duration;
        i_start = std::clock();

        std::vector<int> nums;
        for (int i = 0; i < n; i ++) {
                nums.push_back(i);
        }
        ::shuffle<int>(nums);

        BST<int> bst;
        int i = 0;
        while (i < n) {
                bst.insert(nums[i]);
                i++;
        }
        i_end =  std::clock();
        duration = (i_end - i_start) / (double) CLOCKS_PER_SEC;
        std::cout << "Insertion: " << duration << std::endl;


        f_start = std::clock();
        int j = 0;
        while (j < n) {
                bst.find(nums[j]);
                j++;
        }
        f_end = std::clock();
        duration = (f_end - f_start ) / (double) CLOCKS_PER_SEC;
        std::cout << "Search: " << duration << std::endl;


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

