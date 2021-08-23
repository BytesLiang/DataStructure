#ifndef __STACK__
#define __STACK__
#include "../vector/vector.h"

template <typename T>
class Stack : public Vector<T>
{
public:
    void puch(T const &e) //入栈
    {
        this->insert(this->size(), e);
    }
    T pop() //出栈
    {
        return this->remove(this->size() - 1);
    }
    T &top() //取顶
    {
        return (*this)[this->size() - 1];
    }
};
#endif