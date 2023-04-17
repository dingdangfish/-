#include"../../vector/vector.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath> 
using namespace std;
const int MAX = 30;
const int DONE = 1;


//栈定义 
template <typename T> class Stack : public Vector<T>{
public:
	Stack(int MaxStackSize = 10);//规定最大堆栈大小
	~Stack() { delete[] stack; }
	bool IsEmpty() const { return top == -1; }//判断栈中元素是否为空
	bool IsFull() const { return top == MaxTop; }//判断栈中元素达到规定最大堆栈大小，若达到栈顶为Maxtop
	T Top() const;
	Stack<T>& Add(const T& x);
	Stack<T>& Del(T& x);
	void MakeEmpty() { top = -1; } //清空栈
	void print() {
		for (int i; i < top + 1; i++) {
			cout << stack[i] << '\t';
		}
		cout << endl;
	}
private:
	int top;//栈顶
	int MaxTop;//最大的栈顶值
	T* stack;//堆栈元素数组
};
template<class T>
Stack<T>::Stack(int MaxStackSize) {
	MaxTop = MaxStackSize - 1;
	stack = new T[MaxStackSize];
	top = -1;
}
template<class T>
Stack<T>& Stack<T>::Add(const T& x) {
	if (IsFull())
	{
		cout << "no memory;" << endl;return *this;
	}
	top = top + 1;
	stack[top] = x;
	return *this;
}
template<class T>
Stack<T>& Stack<T>::Del(T& x) {
	if (IsEmpty())
	{
		cout << "no element" << endl;return *this;
	}
	x = stack[top];
	top = top - 1;
	return *this;
}
//返回栈顶
template<class T>
T Stack<T>::Top() const {
	return stack[top];
}

//判断一个字符是否为数字
bool isNum(char c) {
	if ((c > '0' || c == '0') && (c < '9' || c == '9'))
		return true;
	else
		return false;
}

//删除字符串中的空格 
void deleteBlank(string& s) {
	string::iterator i = s.begin();
	while ((i = find(i, s.end(), ' ')) != s.end())
		s.erase(i);
}
