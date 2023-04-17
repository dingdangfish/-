#include<iostream>
#include<algorithm>
#include<stack>
#include<time.h>
using namespace std;

int n;	//柱子数量 
int max_area;	//记录当前最大面积 
int area;	//记录以当前柱子为高的最大面积 
int height[10000];	//存储柱子高度 
stack<int> s;	//存储高度递增的柱子的数组下标 

int main()
{
	srand(time(0));//重置时间
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
			while (!s.empty() && height[s.top()] > height[i])	//栈非空且第i根柱子高度栈顶柱子高度，此时不能入栈，开始计算面积 
			{
				if (s.size() == 1) area = height[s.top()];	//当栈中仅有一个元素，矩形高为柱子高度宽为1 
				else area = height[s.top()] * (i - s.top());	//当栈中有多个元素，矩形高为栈顶柱子高度，宽为左右第一个比当前柱子矮的两柱子的间距即i-s.top 
				max_area = max(max_area, area);	//与之前记录的最大面积作比较，更新最大面积 
				s.pop();	//已做过高的柱子出栈 
			}
			s.push(i);	//栈空或者栈顶柱子高度小于第i根柱子高度，下标入栈 
		}
		cout << endl;
		cout << "面积为" << max_area << endl;;
		max_area = 0;
	}
	return 0;
}