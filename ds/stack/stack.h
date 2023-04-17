#include"../../vector/vector.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath> 
using namespace std;
const int MAX = 30;
const int DONE = 1;


//ջ���� 
template <typename T> class Stack : public Vector<T>{
public:
	Stack(int MaxStackSize = 10);//�涨����ջ��С
	~Stack() { delete[] stack; }
	bool IsEmpty() const { return top == -1; }//�ж�ջ��Ԫ���Ƿ�Ϊ��
	bool IsFull() const { return top == MaxTop; }//�ж�ջ��Ԫ�شﵽ�涨����ջ��С�����ﵽջ��ΪMaxtop
	T Top() const;
	Stack<T>& Add(const T& x);
	Stack<T>& Del(T& x);
	void MakeEmpty() { top = -1; } //���ջ
	void print() {
		for (int i; i < top + 1; i++) {
			cout << stack[i] << '\t';
		}
		cout << endl;
	}
private:
	int top;//ջ��
	int MaxTop;//����ջ��ֵ
	T* stack;//��ջԪ������
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
//����ջ��
template<class T>
T Stack<T>::Top() const {
	return stack[top];
}

//�ж�һ���ַ��Ƿ�Ϊ����
bool isNum(char c) {
	if ((c > '0' || c == '0') && (c < '9' || c == '9'))
		return true;
	else
		return false;
}

//ɾ���ַ����еĿո� 
void deleteBlank(string& s) {
	string::iterator i = s.begin();
	while ((i = find(i, s.end(), ' ')) != s.end())
		s.erase(i);
}
