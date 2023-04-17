//ps:9-24�д�������ͬѧ�ģ�Complex�ඨ�岻���ر����

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
	M1.write_Imaginary(m1);//��ʵ�������鲿���ģ�����ڵ��ڵ�Ч��
	M1.write_Real(0.0); //��Ϊ��ģ�����ʱ��Ƚ�ʵ�������轫m1����ʵ������ģ����Ⱥ����ڴ����鲿����ʵ����С��m1ʹ�ñ��ų����⡣
	M1.write_modulus();//��m1�����鲿�Ͳ������������
	M1.write_arg();
	M2.write_Imaginary(m2);//ͬ��
	M2.write_Real(0.0);//��Ϊģ�����ʱ�����轫m1��ʵ������ʹ�ô����鲿��ʹʵ��С��m1������������С�ڵķ�Χ��
	M2.write_modulus();
	M2.write_arg();//����˵����ȫ���鲿��������ҿ����䣬ȫ��ʵ���������ұ�����
	Rank a = V.search(M1) + 1, b = V.search(M2) + 1;//search����ֵ�ǲ���������Ҫ���m1,m2�����ֵ�������Ҫ��һ
	Vector<Complex> Result(V, a, b);
	return Result;
}

int main()
{
	srand(time(0));//ÿ�����ɲ�һ�����������
	Complex A[10];//���帴����
	cout << "���ɵĸ�������������" << endl;
	//���ɸ���������� 
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

	//����
	cout << endl;
	v.unsort();
	cout << "����" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
	}
	cout << endl;

	//����
	cout << endl;
	int w;
	w = v.find(A[9]);
	cout << endl << "ԭ���������һ��Ԫ�����Һ��λ��Ϊ" << endl << w << endl;

	//����
	cout << endl;
	Vector<Complex>v2(A, 10);
	v2.insert(10, A[rand() % (10)]);
	cout << "�����һλ�����������" << endl;
	for (int j = 0; j < v2.size(); j++)
	{
		v2[j].display();
	}
	cout << endl;

	//ɾ��
	cout << endl;
	Vector<Complex>v3(A, 10);
	v3.remove(0, 4);
	cout << "ɾ������[1��4)���µ�����" << endl;
	for (int j = 0; j < v3.size(); j++)
	{
		v3[j].display();
	}
	cout << endl;

	//Ψһ��
	cout << endl;
	Vector<Complex>v4(A, 10);
	cout << "��ԭ����Ψһ���������µ�����" << endl;
	v4.deduplicate();
	for (int j = 0; j < v4.size(); j++)
	{
		v4[j].display();
	}
	cout << endl;

	cout << endl;
	int n = 0;
	n = v.disordered();//��¼������
	if (n != 0) {
		cout << "ԭ����������Ϊ�������������������" << endl;
	}

	//��������������ʱ
	cout << endl;
	Vector<Complex>v5(A, 10);
    DWORD startTime = GetTickCount();//��ʱ��ʼ
	v5.sort(0, v5.size(), 1);
	for (int i = 0; i < 214748364; i++)//���ڵ�һ����������ʱ̫���޷���ʾ�������ÿ���������˸�һ����ѭ�����ڱȽ������ʱ
    {
        i++;
    }
    DWORD endTime = GetTickCount();//��ʱ����
    cout << "������������+ѭ����ʱ��" << endTime - startTime << "ms" << endl;

	//˳������������ʱ
	cout << endl;
	DWORD startTime2 = GetTickCount();//��ʱ��ʼ
	v5.sort(0, v5.size(), 1);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime2 = GetTickCount();//��ʱ����
	cout << "˳����������+ѭ����ʱ��" << endTime2 - startTime2 << "ms" << endl;

	//��������������ʱ
	cout << endl;
	DWORD startTime3 = GetTickCount();//��ʱ��ʼ
	v5.sort(v5.size(), 0, 1);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime3 = GetTickCount();//��ʱ����
	cout << "������������+ѭ����ʱ��" << endTime3 - startTime3 << "ms" << endl;

	cout << endl;
	Vector<Complex>v6(A, 10);
	//��������
	v6.unsort();
	cout << "�������Һ�������Ϊ��" << endl;
	for (int j = 0; j < v6.size(); j++)
	{
		v6[j].display();
	}
	n = v6.disordered();//��¼������
	cout << endl;
	if (n != 0) {
		cout << "��ǰ����������Ϊ����������й鲢����" << endl;
	}

	//����鲢������ʱ
	cout << endl;
	DWORD startTime4 = GetTickCount();//��ʱ��ʼ
	v6.sort(0, v6.size(), 3);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime4 = GetTickCount();//��ʱ����
	cout << "����鲢����+ѭ����ʱ��" << endTime4 - startTime4 << "ms" << endl;

	//˳��鲢������ʱ
	cout << endl;
	DWORD startTime5 = GetTickCount();//��ʱ��ʼ
	v6.sort(0, v6.size(), 3);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime5 = GetTickCount();//��ʱ����
	cout << "˳��鲢����+ѭ����ʱ��" << endTime5 - startTime5 << "ms" << endl;

	//����鲢������ʱ
	cout << endl;
	DWORD startTime6 = GetTickCount();//��ʱ��ʼ
	v6.sort(v6.size(),0, 3);
	for (int i = 0; i < 214748364; i++)
	{
		i++;
	}
	DWORD endTime6 = GetTickCount();//��ʱ����
	cout << "����鲢����+ѭ����ʱ��" << endTime6 - startTime6 << "ms" << endl;

	//�������
	cout << endl;
	Vector<Complex>v7(A, 10);
	v7.sort(0, v7.size(), 3);
	cout << "˳������Ϊ:" ;
	for (int j = 0; j < v7.size(); j++)
	{
		v7[j].display();
	}
	double m1 , m2 ;//������ҵ�����
	cout<<endl;
	cout << "������ҵ�ģ������[m1,m2)";
	cout << endl;
	cout << "m1=";
	cin >> m1;
	cout << "m2=";
	cin >> m2;
	Vector<Complex> Finded;
	Finded = partModulusSearch(v7, m1, m2);
	cout << "���ҽ��Ϊ:" << endl;
	for (int j = 0; j < Finded.size(); j++)
	{
		Finded[j].display();
	}
	cout << endl;
	return 0;
}