#include <iostream>
#include "linkedlist.h"

void test_linked_list()
{
        LinkedList<int> ln;
        ln.push_front(1);
        ln.push_front(2);
        ln.push_front(5);
        std::cout << ln << std::endl;

        std::cout << ln.find(3) << std::endl;
        std::cout << *ln.find(1) << std::endl;

        ln.remove(1);
        std::cout << ln << std::endl;

        ln.remove(3);
        std::cout << ln << std::endl;
}

//void test_linked_list_speed();
//{

//}
