//ps:9-24行代码借鉴了同学的，Complex类定义不是特别清楚

#include<time.h>
#include<ctime>
#include<iostream>
#include"../../vector/vector.h"
#include "../../complex/complex.h"
#include<Windows.h>
using namespace std;
Vector<Complex> partModulusSearch(Vector<Complex>const& V, double m1, double m2)
{
	Complex M1, M2;
	M1.write_Imaginary(m1);//把实数存在虚部达成模长大于等于的效果
	M1.write_Real(0.0); //因为当模长相等时会比较实部，假设将m1存在实部会有模长相等后，由于存在虚部导致实部会小于m1使得被排除在外。
	M1.write_modulus();//将m1存在虚部就不会有这个问题
	M1.write_arg();
	M2.write_Imaginary(m2);//同理
	M2.write_Real(0.0);//因为模长相等时，假设将m1存实部，会使得存在虚部，使实部小于m1而被包括在了小于的范围内
	M2.write_modulus();
	M2.write_arg();//简单来说就是全存虚部就是左闭右开区间，全存实部就是左开右闭区间
	Rank a = V.search(M1) + 1, b = V.search(M2) + 1;//search到的值是不大于满足要求的m1,m2的最大值，因此需要加一
	Vector<Complex> Result(V, a, b);
	return Result;
}

int main()
{
	srand(time(0));//每次生成不一样的随机向量
	Complex A[10];//定义复数类
	cout << "生成的复数无序向量：" << endl;
	//生成复数类的数组 
	for (int j = 0; j < 10; j++)
	{
		A[j].write_Real(rand() % 100 / 10.0);
		A[j].write_Imaginary(rand() % 100 / 10.0);
		A[j].write_modulus();
		A[j].write_arg();
		A[j].display();
	}
	cout << endl;
	Vector<Complex>v(A, 10);

	//置乱
	cout << endl;
	v.unsort();
	cout << "置乱" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
	}
	cout << endl;

	//查找
	cout << endl;
	int w;
	w = v.find(A[9]);
	cout << endl << "原向量组最后一个元素置乱后的位置为" << endl << w << endl;

	//插入
	cout << endl;
	Vector<Complex>v2(A, 10);
	v2.insert(10, A[rand() % (10)]);
	cout << "在最后一位插入随机向量" << endl;
	for (int j = 0; j < v2.size(); j++)
	{
		v2[j].display();
	}
	cout << endl;

	//删除
	cout << endl;
	Vector<Complex>v3(A, 10);
	v3.remove(0, 4);
	cout << "删除区间[1，4)后新的向量" << endl;
	for (int j = 0; j < v3.size(); j++)
	{
		v3[j].display();
	}
	cout << endl;

	//唯一化
	cout << endl;
	Vector<Complex>v4(A, 10);
	cout << "对原向量唯一化操作后新的向量" << endl;
	v4.deduplicate();
	for (int j = 0; j < v4.size(); j++)
	{
		v4[j].display();
	}
	cout << endl;

	cout << endl;
	int n = 0;
	n = v.disordered();//记录逆序数
	if (n != 0) {
		cout << "原复数向量组为乱序，下面进行起泡排序：" << endl;
	}

	//乱序起泡排序用时
	cout << endl;
	Vector<Complex>v5(A, 10);
    DWORD startTime = GetTickCount();//计时开始
	v5.sort(0, v5.size(), 1);
	for (int i = 0; i < 214748364; i++)//由于单一起泡排序用时太少无法显示，因此在每个排序后加了个一样的循环用于比较相对用时
    {
        i++;
    }
    DWORD endTime = GetTickCount();//计时结束
    cout << "乱序起泡排序+循环用时：" << endTime - startTime << "ms" << endl;

	//顺序起泡排序用时
	cout << endl;
	DWORD startTime2 = GetTickCount();//计时开始
	v5.sort(0, v5.size(), 1);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime2 = GetTickCount();//计时结束
	cout << "顺序起泡排序+循环用时：" << endTime2 - startTime2 << "ms" << endl;

	//逆序起泡排序用时
	cout << endl;
	DWORD startTime3 = GetTickCount();//计时开始
	v5.sort(v5.size(), 0, 1);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime3 = GetTickCount();//计时结束
	cout << "逆序起泡排序+循环用时：" << endTime3 - startTime3 << "ms" << endl;

	cout << endl;
	Vector<Complex>v6(A, 10);
	//重新置乱
	v6.unsort();
	cout << "重新置乱后向量组为：" << endl;
	for (int j = 0; j < v6.size(); j++)
	{
		v6[j].display();
	}
	n = v6.disordered();//记录逆序数
	cout << endl;
	if (n != 0) {
		cout << "当前复数向量组为乱序，下面进行归并排序：" << endl;
	}

	//乱序归并排序用时
	cout << endl;
	DWORD startTime4 = GetTickCount();//计时开始
	v6.sort(0, v6.size(), 3);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime4 = GetTickCount();//计时结束
	cout << "乱序归并排序+循环用时：" << endTime4 - startTime4 << "ms" << endl;

	//顺序归并排序用时
	cout << endl;
	DWORD startTime5 = GetTickCount();//计时开始
	v6.sort(0, v6.size(), 3);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime5 = GetTickCount();//计时结束
	cout << "顺序归并排序+循环用时：" << endTime5 - startTime5 << "ms" << endl;

	//逆序归并排序用时
	cout << endl;
	DWORD startTime6 = GetTickCount();//计时开始
	v6.sort(v6.size(),0, 3);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime6 = GetTickCount();//计时结束
	cout << "逆序归并排序+循环用时：" << endTime6 - startTime6 << "ms" << endl;

	//区间查找
	cout << endl;
	Vector<Complex>v7(A, 10);
	v7.sort(0, v7.size(), 3);
	cout << "顺序数组为:" ;
	for (int j = 0; j < v7.size(); j++)
	{
		v7[j].display();
	}
	double m1 , m2 ;//区间查找的区间
	cout<<endl;
	cout << "输入查找的模长区间[m1,m2)";
	cout << endl;
	cout << "m1=";
	cin >> m1;
	cout << "m2=";
	cin >> m2;
	Vector<Complex> Finded;
	Finded = partModulusSearch(v7, m1, m2);
	cout << "查找结果为:" << endl;
	for (int j = 0; j < Finded.size(); j++)
	{
		Finded[j].display();
	}
	cout << endl;
	return 0;
}