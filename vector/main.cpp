#include "vector.h"
#include <iostream>

using namespace std;

template <typename T>
void printVector(T &e)
{
    cout << e <<'\t';
}
void vectorTest()
{
    Vector<int> v(10, 5, 2);
    v.insert(3, 5);
    v.insert(8);
    v.sort(2);
    cout << v.search(2);
    v.traverse(printVector);
    getchar();
}
int main()
{
    vectorTest();
    return 0;
}