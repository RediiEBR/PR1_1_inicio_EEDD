#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include "vEstatico.h"
#include "forwardList.h"
#include <forward_list>
using namespace std;
int main()
{
    int i=-100;
    forward_list<int> list;
    while(i<100)
    {
        list.push_front(i);
        i++;
    }
    i++;
    return 0;
}