#ifndef __LISTNODE__
#define __LISTNODE__

#include <stddef.h>

typedef int Rank;
#define ListNodePosi(T) ListNode<T> * //列表节点位置

template <typename T>
struct ListNode
{
    /*成员*/
    T data;               //数值
    ListNodePosi(T) pred; //前驱
    ListNodePosi(T) succ; //后继
    /*构造函数*/
    ListNode() {}
    ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
        : data(e), pred(p), succ(s)
    {
    }
    /*操作接口*/
    ListNodePosi(T) insertAsPred(T const &e); //节点前插入
    ListNodePosi(T) insertAsSucc(T const &e); //节点后插入
};
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e) //前插入
{
    ListNodePosi(T) x = new ListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}
template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e) //后插入
{
    ListNodePosi(T) x = new ListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}
#endif
