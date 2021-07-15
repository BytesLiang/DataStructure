/* 自学C++语言 */
#include "complex.h"
#include <iostream>

using namespace std;

template <class T>
class Mycode
{
public:
    T value = 20;
    Mycode(T v)
    {
        value = v;
        cout << "begin!";
    }
};
int main()
{
    Mycode<int> mycode(20);
    cout << mycode.value;
    getchar();
    getchar();
    return 0;
}