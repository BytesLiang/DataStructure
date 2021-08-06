#include "list.h"
#include <iostream>

using namespace std;

template <typename T>
void printList(T &e)
{
    cout << e << '\t';
}
void listTest()
{
    List<int> l;
    for (int i = 0; i < 10;i++)
    {
        l.insertAsFirst(rand()%30);
    }
    l.insertAsLast(0);
    l.insertAfter(l.first()->succ, 1);
    l.traverse(printList);
    l.sort();
    l.traverse(printList);
}

int main()
{
    listTest();
    getchar();
}