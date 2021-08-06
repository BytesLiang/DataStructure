#ifndef __LIST__
#define __LIST__

#include "listnode.h"

typedef int Rank;

template <typename T>
class List
{
private:
    int _size;
    ListNodePosi(T) header;  //头
    ListNodePosi(T) trailer; //尾

protected:
    void init();                                              //列表创建初始化
    int clear();                                              //清除所有节点
    void copyNodes(ListNodePosi(T), int);                     //复制列表
    void merge(ListNodePosi(T) &, int, ListNodePosi(T), int); //归并算法
    void mergeSort(ListNodePosi(T) &, int);                   //归并排序
    void selectionSort(ListNodePosi(T), int);                 //选择排序
    void insertionSort(ListNodePosi(T), int);                 //插入排序
    void bubbleSort(ListNodePosi(T), int);                    //冒泡排序

public:
    /*构造函数*/
    List();                                //空列表
    List(List<T> const &L);                //整体复制列表
    List(List<T> const &L, Rank r, int n); //复制自r起的n项
    List(ListNodePosi(T) p, int n);        //复制自位置p起的n项
    /*析构函数*/
    ~List();
    /*只读访问接口*/
    Rank size() const //规模
    {
        return _size;
    }
    bool empty() const //判空
    {
        return _size <= 0;
    }
    T &operator[](Rank r) const;  //重载[]运算符,循秩访问
    ListNodePosi(T) first() const //首节点位置
    {
        return header->succ;
    }
    ListNodePosi(T) last() const //末节点位置
    {
        return trailer->pred;
    }
    bool vaild(ListNodePosi(T) p) //判断位置P是否对外合法
    {
        return p && (trailer != p) && (header != p);
    }
    int disordered() const;                //判断列表是否已排序
    ListNodePosi(T) find(T const &e) const //无序列表查找
    {
        return find(e, _size, trailer);
    }
    ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const; //无序列表区间查找
    ListNodePosi(T) search(T const &e) const                          //有序列表查找
    {
        return search(e, _size, trailer);
    }
    ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const; //有序列表区间查找
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);                //在p及其前n-1个后继中选出最大者
    ListNodePosi(T) selectMax()                                         //整体最大者
    {
        return selectMax(header->succ, _size);
    }
    /*可写访问接口*/
    ListNodePosi(T) insertAsFirst(T const &e);                   //作为首节点插入
    ListNodePosi(T) insertAsLast(T const &e);                    //作为末节点插入
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const &e); //作为前驱插入
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const &e);  //作为后继插入
    T remove(ListNodePosi(T) p);                                 //删除节点
    void sort(ListNodePosi(T) p, int n);                         //列表区间排序
    void sort()                                                  //列表整体排序
    {
        sort(first(), _size);
    }
    int deduplicate(); //无序去重
    int uniquify();    //有序去重
    void reverse();    //前后倒置
    /*遍历*/
    void traverse(void (*)(T &)); //函数指针遍历
    template <typename VST>
    void traverse(VST &); //函数对象遍历
};
template <typename T>
void List<T>::init() //列表初始化
{
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ = trailer;
    header->pred = NULL;
    trailer->pred = header;
    trailer->succ = NULL;
    _size = 0;
}
template <typename T>
T &List<T>::operator[](Rank r) const //重载下标操作符
{
    ListNodePosi(T) p = first();
    while (0 < r--)
        p = p->succ;
    return p->data;
}
template <typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p) const //区间内查找
{
    while (0 < n--)
        if (e == (p = p->pred)->data)
            return p;
    return NULL;
}
template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e) //作为首节点插入
{
    _size++;
    return header->insertAsSucc(e);
}
template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e) //作为末节点插入
{
    _size++;
    return trailer->insertAsPred(e);
}
template <typename T>
ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const &e) //作为前驱插入
{
    _size++;
    return p->insertAsPred(e);
}
template <typename T>
ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const &e) //作为后继插入
{
    _size++;
    return p->insertAsSucc(e);
}
template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) //复制列表
{
    init();
    while (n--)
    {
        insertAsLast(p->data);
        p = p->succ;
    }
}
template <typename T>
List<T>::List() //空列表
{
    init();
}
template <typename T>
List<T>::List(ListNodePosi(T) p, int n) //区间复制
{
    copyNodes(p, n);
}
template <typename T>
List<T>::List(List<T> const &L) //整体复制
{
    copyNodes(L.first(), L._size);
}
template <typename T>
List<T>::List(List<T> const &L, int r, int n) //从第r项开始复制
{
    copyNodes(L[r], n);
}
template <typename T>
T List<T>::remove(ListNodePosi(T) p) //删除P节点
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}
template <typename T>
List<T>::~List() //析构函数
{
    clear();
    delete header;
    delete trailer;
}
template <typename T>
Rank List<T>::clear() //清空列表
{
    Rank oldSize = _size;
    while (0 < _size)
        remove(header->succ);
    return oldSize;
}
template <typename T>
int List<T>::deduplicate() //无序列表去重
{
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    Rank r = 0;
    while (trailer != (p = p->succ))
    {
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}
template <typename T>
void List<T>::traverse(void (*visit)(T &)) //利用函数指针遍历
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}
template <typename T>
template <typename VST>
void List<T>::traverse(VST &visit) //利用函数对象遍历
{
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
        visit(p->data);
}
template <typename T>
Rank List<T>::uniquify() //有序列表去重
{
    if (_size < 2)
        return 0;
    int oldSize = _size;
    ListNodePosi(T) p;
    ListNodePosi(T) q;
    for (p = header, q = p->succ; trailer != q; p = q, q = q->succ)
        if (p->data == q->data)
        {
            remove(q);
            q = p;
        }
    return oldSize - _size;
}
template <typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T) p) const //有序列表区间查找
{
    while (0 <= n--)
        if (((p = p->pred)->data) <= e)
            break;
    return p;
}
template <typename T>
void List<T>::sort(ListNodePosi(T) p, int n) //列表区间排序
{
    // switch (method)
    // {
    // case 1:
    mergeSort(p, n); //插入排序
    // case 2:
    //     selectionSort(p, n); //选择排序
    // }
}
template <typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n) //插入排序
{
    for (int r = 0; r < n; r++)
    {
        ListNodePosi(T) q = p->pred;
        for (int t = r; t > 0; t--)
        {
            if (p->data >= q->data)
                break;
            q = q->pred;
        }
        insertAfter(q, p->data);
        p = p->succ;
        remove(p->pred);
    }
}
template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) //选择排序
{
    for (; n > 1; n--)
    {
        ListNodePosi(T) min = p;
        ListNodePosi(T) q = p;
        for (int i = 1; i < n; i++)
        {
            q = q->succ;
            if (q->data < min->data)
                min = q;
        }
        ListNodePosi(T) head = insertBefore(p, min->data);
        remove(min);
        p = head->succ;
    }
}
template <typename T>
bool bubble(ListNodePosi(T) p, int n) //扫描交换
{
    bool sorted = true;
    ListNodePosi(T) q = p->succ;
    for (; n > 0; n--)
    {
        if (p->data > q->data)
        {
            sorted = false;
            p->pred->succ = q;
            q->succ->pred = p;
            p->succ = q->succ;
            q->pred = p->pred;
            q->succ = p;
            p->pred = q;
            p = q;
        }
        p = p->succ;
        q = p->succ;
    }
    return sorted;
}
template <typename T>
void List<T>::bubbleSort(ListNodePosi(T) p, int n) //起泡排序
{
    ListNodePosi(T) head = p->pred;
    while (!bubble(head, n--)) //逐趟扫描交换
        ;
}
template <typename T>
void List<T>::merge(ListNodePosi(T) & p, int n, ListNodePosi(T) q, int m)
{
    ListNodePosi(T) head = p->pred;
    while (0 < m)
    {
        if ((0 < n) && (p->data <= q->data))
        {
            if (q == (p = p->succ))
                break;
            n--;
        }
        else
        {
            insertBefore(p, remove((q = q->succ)->pred));
            m--;
        }
    }
    p = head->succ;
}
template <typename T>
void List<T>::mergeSort(ListNodePosi(T) & p, int n) //归并排序
{
    if (n < 2)
        return;
    int m = n >> 1;
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++)
        q = q->succ;
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, q, n - m);
}
#endif