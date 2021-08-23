#include "../list/list.h"
template <typename T>
class Queue : public List<T> //队列
{
public:
    void enqueue(T const &e) //入队
    {
        this->insertAsLast(e);
    }
    T dequeue() //出队
    {
        return this->remove(thid->first());
    }
    T &front() //队首
    {
        return this->first()->data;
    }
}