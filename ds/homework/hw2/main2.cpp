#include<iostream>
#include<algorithm>
#include<stack>
#include<time.h>
using namespace std;

int n;	//�������� 
int max_area;	//��¼��ǰ������ 
int area;	//��¼�Ե�ǰ����Ϊ�ߵ������� 
int height[10000];	//�洢���Ӹ߶� 
stack<int> s;	//�洢�߶ȵ��������ӵ������±� 

int main()
{
	srand(time(0));//����ʱ��
	for (int j = 1;j <= 10;j++) {
		n = (rand() % 10) + 1;
		cout << "n=" << n << " height=";
		for (int i = 0;i < n;i++) {
			height[i] = (rand() % 105) + 1;
			if (i != n) {
				cout << height[i] << ' ';
			}
		}
		for (int i = 0;i <= n;i++)
		{
			while (!s.empty() && height[s.top()] > height[i])	//ջ�ǿ��ҵ�i�����Ӹ߶�ջ�����Ӹ߶ȣ���ʱ������ջ����ʼ������� 
			{
				if (s.size() == 1) area = height[s.top()];	//��ջ�н���һ��Ԫ�أ����θ�Ϊ���Ӹ߶ȿ�Ϊ1 
				else area = height[s.top()] * (i - s.top());	//��ջ���ж��Ԫ�أ����θ�Ϊջ�����Ӹ߶ȣ���Ϊ���ҵ�һ���ȵ�ǰ���Ӱ��������ӵļ�༴i-s.top 
				max_area = max(max_area, area);	//��֮ǰ��¼�����������Ƚϣ����������� 
				s.pop();	//�������ߵ����ӳ�ջ 
			}
			s.push(i);	//ջ�ջ���ջ�����Ӹ߶�С�ڵ�i�����Ӹ߶ȣ��±���ջ 
		}
		cout << endl;
		cout << "���Ϊ" << max_area << endl;;
		max_area = 0;
	}
	return 0;
}