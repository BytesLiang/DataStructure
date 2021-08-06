#ifndef __VECTOR__
#define __VECTOR__

#include "..\fibonacci\Fib.h"
#include <iostream>
#include <stdlib.h>

typedef int Rank;
#define DEFAULT_CAPACITY 3

using namespace std;

template <typename T>
class Vector
{
protected:
    Rank _size;
    int _capacity;
    T *_elem;                                    //规模、容量、数据区
    void copyFrom(T const *A, Rank lo, Rank hi); //复制数组区间A[lo,hi]
    void expand();                               //扩容
    void shrink();                               //压缩
    bool bubble(Rank lo, Rank hi);               //扫描交换
    void bubbleSort(Rank lo, Rank hi);           //起泡排序
    Rank max(Rank lo, Rank hi);                  //选取最大元素
    void selectionSort(Rank lo, Rank hi);        //选择排序
    void merge(Rank lo, Rank mi, Rank hi);       //归并算法
    void mergeSort(Rank lo, Rank hi);            //归并排序
    Rank partition(Rank lo, Rank hi);            //轴点构造
    void quickSort(Rank lo, Rank hi);            //快速排序
    void heapSort(Rank lo, Rank hi);             //堆排序
public:
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c,规模为s,所有元素初始为v
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }
    Vector(T const *A, Rank lo, Rank hi) //数组区间复制
    {
        copyFrom(A, lo, hi);
    }
    Vector(T const *A, Rank n) //数组整体复制
    {
        copyFrom(A, 0, n);
    }
    Vector(Vector<T> const &V, Rank lo, Rank hi) //向量区间复制
    {
        copyFrom(V._elem, 0, lo, hi);
    }
    Vector(Vector<T> const &V) //向量整体复制
    {
        copyFrom(V._elem, 0, V._size);
    }
    ~Vector() //析构函数，释放内部空间
    {
        delete[] _elem;
    }
    /*只读访问接口*/
    Rank size() const //规模
    {
        return _size;
    }
    bool empty() const //判空
    {
        return !_size;
    }
    int disordered() const;     //判断向量是否已排序
    Rank find(T const &e) const //无序向量整体查找
    {
        return find(e, 0, _size);
    }
    Rank find(T const &e, Rank lo, Rank hi) const; // 无序向量区间查找
    Rank search(T const &e) const                  //有序向量整体查找
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const &e, Rank lo, Rank hi) const; //有序向量区间查找
    /*可写访问接口*/
    T &operator[](Rank r) const;             //重载下标操作符
    Vector<T> &operator=(Vector<T> const &); //重载赋值操作符
    T remove(Rank r);                        //删除秩为r的元素
    int remove(Rank lo, Rank hi);            // 删除秩在区间[lo,hi]之间的元素
    Rank insert(Rank r, T const &e);         //插入元素
    Rank insert(T const &e)                  //作为末元素插入
    {
        return insert(_size, e);
    }
    void sort(Rank lo, Rank hi, int method); //局部排序
    void sort(int method)                    //整体排序
    {
        sort(0, _size, method);
    }
    void unsort(Rank lo, Rank hi); //局部置乱
    void unsort()                  //整体置乱
    {
        unsort(0, _size);
    }
    int deduplicate();            //无序去重
    int uniquify();               //有序去重
    void traverse(void (*)(T &)); //指针遍历
    template <typename VST>
    void traverse(VST &); //对象遍历
};
template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) //区间复制
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
        _elem[_size++] = A[lo++];
}
template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &V) //=操作符重载
{
    if (_elem)
        delete[] _elem;
    copyFrom(V._elem, 0, V.size());
    return *this;
}
template <typename T>
void Vector<T>::expand() //扩容
{
    if (_size < _capacity)
        return; //尚未满员时，不必扩容
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY; //不低于最小容量
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //容量加倍
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}
template <typename T>
void Vector<T>::shrink() //缩容
{
    if (_capacity < DEFAULT_CAPACITY << 1)
        return;
    if (_size << 2 > _capacity) //以25%为界
        return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1]; //容量减半
    for (int i = 0; i < _size; i++)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}
template <typename T>
T &Vector<T>::operator[](Rank r) const //[]操作符重载
{
    return _elem[r];
}
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) //置乱向量区间
{
    T *V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
}
template <typename T>
static bool lt(T *a, T *b)
{
    return lt(*a, *b);
}
template <typename T>
static bool lt(T &a, T &b)
{
    return a < b;
}
template <typename T>
static bool eq(T *a, T *b)
{
    return eq(*a, *b);
}
template <typename T>
static bool eq(T &a, T &b)
{
    return a == b;
}
template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const //查找
{
    while ((lo < hi--) && (e != _elem[hi]))
        ;
    return hi;
}
template <typename T>
Rank Vector<T>::insert(Rank r, T const &e) //向量插入元素
{
    expand();
    for (int i = _size; i > r; i--)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    _size++;
    return r;
}
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) //区间向量删除
{
    if (lo == hi)
        return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}
template <typename T>
T Vector<T>::remove(Rank r) //删除向量
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}
template <typename T>
int Vector<T>::deduplicate() //无序向量去重
{
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    return oldSize - _size;
}
template <typename T>
void Vector<T>::traverse(void (*visit)(T &)) // 利用函数指针遍历
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit) // 利用函数对象遍历
{
    for (int i = 0; i < _size; i++)
        visit(_elem[i]);
}
template <typename T>
struct Increase //函数对象：递增一个T类对象
{
    virtual void operator()(T &e)
    {
        e++;
    }
};
template <typename T>
void increase(Vector<T> &V) //统一递增向量中各元素
{
    V.traverse(Increase<T>());
}
template <typename T>
int Vector<T>::disordered() const //向量中逆序相邻元素的数量
{
    int n = 0;
    for (int i = 1; i < _size; i++)
        if (_elem[i - 1] > _elem[i])
            n++;
    return n; //向量有序当且仅当n=0
}
template <typename T>
int Vector<T>::uniquify() //有序向量去重
{
    Rank i = 0, j = 0;
    while (++j < _size)
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j - i;
}
/*
template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) //二分查找算法A
{
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}
*/
/*
template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) // 二分查找算法B,返回元素位置
{
    while (1 < hi - lo)
    {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi;
    }
    return (e == A[lo]) ? lo : -1;
}
*/
template <typename T>
static Rank binSearch(T *A, T const &e, Rank lo, Rank hi) // 二分查找算法C,返回元素位置，相同元素返回秩最大者
{
    while (lo < hi)
    {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi + 1;
    }
    return (e == A[--lo]) ? lo : -1;
}
template <typename T>
static Rank fibSearch(T *A, T const &e, Rank lo, Rank hi) //Fibonacci查找算法
{
    Fib fib(hi - lo);
    while (lo < hi)
    {
        while (hi - lo < fib.get())
            fib.prev();
        Rank mi = lo + fib.get() - 1;
        if (e < A[mi])
            hi = mi;
        else if (A[mi] < e)
            lo = mi + 1;
        else
            return mi;
    }
    return -1;
}
template <typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const //有序向量区间查找
{
    return binSearch(_elem, e, lo, hi); //二分查找
    // return fibSearch(_elem, e, lo, hi); //Fibonacci查找
}
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi, int method) //向量区间排序 method:1~5
{
    switch (method)
    {
    case 1:
        bubbleSort(lo, hi); //起泡排序
        break;
    default:
        mergeSort(lo, hi);
        break;
        // case 2:
        //     selectionSort(lo, hi); //选择排序
        //     break;
        // case 3:
        //     mergeSort(lo, hi); //归并排序
        //     break;
        // case 4:
        //     heapSort(lo, hi); //堆排序
        //     break;
        // default:
        //     quickSort(lo, hi); //快速排序
        //     break;
    }
}
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) //起泡排序
{
    while (!bubble(lo, hi--)) //逐趟扫描交换
        ;
}
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) //扫描交换
{
    bool sorted = true;
    while (++lo < hi)
        if (_elem[lo - 1] > _elem[lo])
        {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    return sorted;
}
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) //归并排序
{
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) //有序向量的归并
{
    T *A = _elem + lo;
    int lb = mi - lo;
    T *B = new T[lb];
    for (Rank i = 0; i < lb; i++)
        B[i] = A[i];
    int lc = hi - mi;
    T *C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
    {
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))
            A[i++] = B[j++];
        if ((k < lc) && (!(j < lb) || (C[k] < B[j])))
            A[i++] = C[k++];
    }
    delete[] B;
}
#endif