#include <iostream>
#include "forwardList.h"

using namespace std;
int main()
{
    forwardList<int> in;
    for (int i = 0; i < 100; ++i)
    {
        in.push_back(i);
    }

    in.size();
    return 0;
}