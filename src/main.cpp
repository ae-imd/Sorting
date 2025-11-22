#include <iostream>
#include <list>
#include "../include/sorting.h"

int main()
{
    int *ptr = new int[5]{-2, 0, -5, 4, 1};
    IMD::bubble_sort(ptr, ptr + 5);

    std::list<int> lst = {1, 2, 3, 4, 5, 6};

    for (int i = 0; i < 5; ++i)
        std::cout << ptr[i] << " ";

    std::cout
        << "Hello, world!" << std::endl;
    return 0;
}
