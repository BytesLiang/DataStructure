/* 自学C++语言 */
#include "complex.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

void error_msg(initializer_list<string> li,int i)
{
    cout << i;
    for(const auto& elem:li)
        cout << elem << " ";
    cerr << __func__;
}
int main()
{
    error_msg({"wo", "shi", "nd"}, 5);
    getchar();
    getchar();
    return 0;
}