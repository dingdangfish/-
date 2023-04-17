#pragma once
#include "vector.h"
#include<stdlib.h>
template<typename T>
inline void Vector<T>::swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template <typename T>//模板名称定义
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}

//扩容expand
template <typename T>
void Vector<T>::expand()
{
	if (_size < _capacity) return;//未满 不扩容 
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY; //保证不低于原来的容量 
	T* oldElem = _elem; _elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[]oldElem;//释放原空间 
}

//缩容shrink
template <typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)return;
	if (_size << 2 > _capacity)return;
	T* oldElem = _elem; _elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)_elem[i] = oldElem[i];
	delete[]oldElem;
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
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

//起泡排序
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (!bubble(lo, hi--));
}

template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi)//在[lo, hi]内找出最大者
{
	Rank max = lo;
	while (++lo < hi)
		if (_elem[lo] >= _elem[max])
		{
			max = lo;
		}
	return max;
}

//选择排序
template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
	while (lo < --hi)
	{
		swap(_elem[max(lo, hi)], _elem[hi]); 
	}
}

template<typename T>//对各自有序的[lo, mi)和[mi, hi)做归并
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)// lo < mi < hi
{//以mi 为界，各自有序的子向量[lo,mi) [mi, hi)
	T* A = _elem + lo; //合并后的向量A[0,hi-lo) = _elem[lo,hi)
	int lb = mi - lo;
	T* B = new T[lb];//前子向量B[0,lb) = _elem[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i++]);//复制前子向量,只有前面的有必要复制，有被覆盖的风险
	int lc = hi - mi;
	T* C = _elem + mi;//前子向量C[0,lc) = _elem[mi,hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)// 将B[j]和C[k]中的小者续至A的末尾
	{
		if ((j < lb) && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || C[k] < B[j])) A[i++] = C[k++];
	}
	delete[]B; //释放临时空间B
}// 归并后得到完整的有序向量 lo,hi

//归并排序
template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return; 
	Rank mi = (lo + hi) / 2; 
	mergeSort(lo, mi);
	mergeSort(mi, hi); 
	merge(lo, mi, hi); 
}

template<typename T>
Rank Vector<T>::partition(Rank lo, Rank hi)
{
	swap(_elem[lo], _elem[lo + rand() % (hi - lo)]);
	T pivot = _elem[lo]; 
	while (lo < hi)
	{
		do hi--;
		while ((lo < hi) && (pivot < _elem[hi])); //向左拓展后缀G
		if (lo < hi)
		{
			_elem[lo] = _elem[hi];//阻挡者归入前缀L
		}
		do lo++;
		while ((lo < hi) && (_elem[lo] < pivot)); //向右拓展前缀L
		if (lo < hi)
		{
			_elem[hi] = _elem[lo]; //阻挡者归入后缀G
		}
	} // assert: quit with lo == hi or hi + 1
	_elem[hi] = pivot; //候选轴点置于前缀、后缀之间，它便名副其实
	return hi; //返回轴点的秩
}

//快速排序
template<typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) // 0 <= lo < hi <= size
{
	if (hi - lo < 2) return; 
	Rank mi = partition(lo, hi); 
	quickSort(lo, mi); quickSort(mi + 1, hi); 
}

template<typename T>
void Vector<T>::heapSort(Rank lo, Rank hi)// 0 <= lo < hi <= size
{
	T* A = _elem + lo;
	Rank n = hi - lo;
	heapify(A, n); 
	while (0 < --n) 
	{
		swap(A[0], A[n]); percolateDown(A, n, 0);
	} 
}

template<typename T>
inline int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] > _elem[i])
		{
			n++;
		}
	}
	return n;//当且仅当n=0时向量有序 
}

///查找
template<typename T>
inline Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	while ((lo < hi--) && (e != _elem[hi])); 
	return hi; 
}

template<typename T>
inline Rank Vector<T>::search(T* S, T const& e, Rank lo, Rank hi) const
{
	while (lo < hi) 
	{
		Rank mi = (lo + hi) >> 1; 
		(e < S[mi]) ? hi = mi : lo = mi + 1;
	} 
	return lo - 1; 
}

template <typename T>
T& Vector<T>::operator[] (Rank r) //重载下标操作符
{
	return _elem[r];
} // assert: 0 <= r < _size

template <typename T>
const T& Vector<T>::operator[] (Rank r) const //仅限于做右值
{
	return _elem[r];
} // assert: 0 <= r < _size

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem)
	{
		delete[]_elem;
	}
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<typename T>
inline T Vector<T>::remove(Rank r)
{
	T e = _elem[r]; 
	remove(r, r + 1); 
	return e; //返回被删除元素
}

template<typename T>
inline int Vector<T>::remove(Rank lo, Rank hi)//删去[lo,hi)
{
	if (lo == hi) return 0; 
	while (hi < _size) _elem[lo++] = _elem[hi++]; 
	_size = lo;
	shrink(); 
	return hi - lo; 
}

template<typename T>
inline Rank Vector<T>::insert(Rank r, T const& e)
{
	expand(); //如必要，先扩容
	for (Rank i = _size; r < i; i--) //自后向前，后继元素
	{
		_elem[i] = _elem[i - 1];//顺次后移一个单元
	}
	_elem[r] = e; _size++; //置入新元素并更新容量
	return r; //返回秩
}

template<typename T>//这是借鉴别人的智慧成果，很方便
inline void Vector<T>::sort(Rank lo, Rank hi, int Case)
{
	switch (Case)
	{
	case 1: bubbleSort(lo, hi); break; //起泡排序
	case 2: selectionSort(lo, hi); break; //选择排序
	case 3: mergeSort(lo, hi); break; //归并排序
	default: quickSort(lo, hi); break; //快速排序
	} //自主选择排序算法以测试
}

//置乱操作
template<typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo; 
	for (Rank i = hi - lo; 1 < i; --i) 
	{
		swap(V[i - 1], V[rand() % i]);
	}
}

template<typename T>
inline int Vector<T>::deduplicate()
{
	Rank oldSize = _size; 
	for (Rank i = 1; i < _size; )
	{
		if (-1 == find(_elem[i], 0, i))
		{
			i++;
		}
		else
		{
			remove(i);
		}
	}
	return oldSize - _size; 
}

template<typename T>
inline int Vector<T>::uniquify()
{
	Rank i = 0, j = 0; //各对互异“相邻”元素的秩
	while (++j < _size) //逐一扫描，直至末元素
	{
		if (_elem[i] != _elem[j]) //跳过雷同者
		{
			_elem[++i] = _elem[j];//发现不同元素时，向前移至紧邻于前者右侧
		}
	}
	_size = ++i; shrink(); //直接截除尾部多余元素
	return j - i; //向量规模变化量，即被删除元素总数
}

template<typename T>
void Vector<T>::traverse(void(*visit)(T&))//借助函数指针机制
{
	for (Rank i = 0; i < _size; i++) visit(_elem[i]);//遍历向量
}

template <typename T>
template <typename VST> 
void Vector<T>::traverse(VST& visit) //借助函数对象机制
{
	for (Rank i = 0; i < _size; i++) visit(_elem[i]);//遍历向量
}
