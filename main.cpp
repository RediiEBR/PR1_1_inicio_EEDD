#include <iostream>
#include <forward_list>
#include "forwardList.h"


int main()
{
    std::forward_list<int>in;
    forwardList<int> ints;
    for (int i = 0; i < 100; ++i)
    {
        in.push_front(i);
       // in.push_back(i);
    }

    //in.size();
    return 0;
}