#pragma once
#include <iostream> 
#include <cmath>
using namespace std;
const double Epslion = 1e-8;//����˫���ȸ������Ƚϴ�С
class Complex
{
public:
    //���캯��
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag), m_modulus(sqrt(imag* imag + real * real)), m_arg(atan2(imag, real) / 180 * acos(-1.0))
    { }
    //���������
        //��ȫ�ֺ�������ʽ����
    //friend Complex operator() ();
    friend Complex operator+(const Complex& c1, const Complex& c2);//��Ԫ�������Է��ʶ����˽�г�Ա
    friend Complex operator+(const Complex& c1, const double m);
    friend Complex operator+(const double m, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const double m);
    friend Complex operator-(const double m, const Complex& c2);
    friend Complex operator*(const Complex& c1, const Complex& c2);
    friend Complex operator*(const Complex& c1, const double m);
    friend Complex operator*(const double m, const Complex& c2);
    friend Complex operator/(const Complex& c1, const Complex& c2);
    friend Complex operator/(const Complex& c1, const double m);
    friend Complex operator/(const double m, const Complex& c2);
    friend bool operator==(const Complex& c1, const Complex& c2);
    friend bool operator==(const Complex& c1, const double m);
    friend bool operator==(const double m, const Complex& c1);
    friend bool operator!=(const Complex& c1, const Complex& c2);
    friend bool operator!=(const Complex& c1, const double m);
    friend bool operator!=(const double m, const Complex& c2);
    friend bool operator> (const Complex& c1, const Complex& c2);
    friend bool operator>(const Complex& c1, const double m);
    friend bool operator>(const double m, const Complex& c1);
    friend bool operator>= (const Complex& c1, const Complex& c2);
    friend bool operator>= (const Complex& c1, const double m);
    friend bool operator>= (const double m, const Complex& c2);
    friend bool operator< (const Complex& c1, const Complex& c2);
    friend bool operator<(const Complex& c1, const double m);
    friend bool operator<(const double m, const Complex& c1);
    friend bool operator<= (const Complex& c1, const Complex& c2);
    friend bool operator<= (const Complex& c1, const double m);
    friend bool operator<= (const double m, const Complex& c2);
    //�Գ�Ա��������ʽ����
    Complex& operator+=(const Complex& c);//����ֵ
    Complex& operator-=(const Complex& c);//����ֵ
    Complex& operator*=(const Complex& c);//�˸�ֵ
    Complex& operator/=(const Complex& c);//����ֵ
    void display();
    void write_Real(double r);//д�뺯��
    void write_Imaginary(double i);
    void write_modulus();
    void write_arg();
    double real() const { return m_real; }//��ȡ����
    double imag() const { return m_imag; }
    double modulus() const { return m_modulus; }
    double arg() const { return m_arg; }
private:
    double m_real;  //ʵ��
    double m_imag;  //�鲿
    double m_modulus;  //ģ�� 
    double m_arg;  //������ֵ����λ�ȡ�
};
inline Complex operator+(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = c1.m_real + c2.m_real;
    c.m_imag = c1.m_imag + c2.m_imag;
    return c;
}
inline Complex operator+(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real + m;
    c.m_imag = c1.m_imag;
    return c;
}
inline Complex operator+(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = c2.m_real + m;
    c.m_imag = c2.m_imag;
    return c;
}

//����-�����
inline Complex operator-(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = c1.m_real - c2.m_real;
    c.m_imag = c1.m_imag - c2.m_imag;
    return c;
}
inline Complex operator-(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real - m;
    c.m_imag = c1.m_imag;
    return c;
}
inline Complex operator-(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = c2.m_real - m;
    c.m_imag = c2.m_imag;
    return c;
}

//����*�����  (a+bi) * (c+di) = (ac-bd) + (bc+ad)i
inline Complex operator*(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
    c.m_imag = c1.m_imag * c2.m_real + c1.m_real * c2.m_imag;
    return c;
}
inline Complex operator*(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real * m;
    c.m_imag = c1.m_imag * m;
    return c;
}
inline Complex operator*(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = c2.m_real * m;
    c.m_imag = c2.m_imag * m;
    return c;
}

//����/�����  (a+bi) / (c+di) = [(ac+bd) / (c2+d2)] + [(bc-ad) / (c2+d2)]i
inline Complex operator/(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = (c1.m_real * c2.m_real + c1.m_imag * c2.m_imag) / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.m_imag = (c1.m_imag * c2.m_real - c1.m_real * c2.m_imag) / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    return c;
}
inline Complex operator/(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real / m;
    c.m_imag = c1.m_imag / m;
    return c;
}
inline Complex operator/(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = m * c2.m_real / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.m_imag = -m * c2.m_imag / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    return c;
}

//����==�����
inline bool operator==(const Complex& c1, const Complex& c2)
{
    if ((abs(c1.m_real - c2.m_real) < Epslion) && (abs(c1.m_imag - c2.m_imag) < Epslion))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator==(const Complex& c1, const double m)
{
    if ((abs(c1.m_modulus - m * m) < Epslion) && (abs(c1.m_imag) < Epslion))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator==(const double m, const Complex& c2)
{
    if ((abs(c2.m_modulus - m * m) < Epslion) && (abs(c2.m_imag) < Epslion))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//����!=�����
inline bool operator!=(const Complex& c1, const Complex& c2)
{
    if (c1 == c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator!=(const Complex& c1, const double m)
{
    if (c1 == m)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator!=(const double m, const Complex& c2)
{
    if (c2 == m)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//����>�����
inline bool operator>(const Complex& c1, const Complex& c2)
{
    if ((c1.m_modulus > c2.m_modulus) || ((abs(c1.m_modulus - c2.m_modulus) < Epslion) && (c1.m_real > c2.m_real)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>(const Complex& c1, const double m)
{
    if (c1.m_modulus > m * m)
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>(const double m, const Complex& c2)
{
    if ((m * m > c2.m_modulus) || ((abs(m - c2.m_modulus) < Epslion) && (abs(c2.m_imag) > Epslion)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//����>=�����
inline bool operator>=(const Complex& c1, const Complex& c2)
{
    if ((c1 > c2) || (c1 == c2))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>=(const Complex& c1, const double m)
{
    if ((c1 > m) || (c1 == m))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>=(const double m, const Complex& c2)
{
    if ((m > c2) || (m == c2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//����<�����
inline bool operator<(const Complex& c1, const Complex& c2)
{
    if (c1 >= c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<(const Complex& c1, const double m)
{
    if (c1 >= m)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<(const double m, const Complex& c2)
{
    if (m >= c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//����<=�����
inline bool operator<=(const Complex& c1, const Complex& c2)
{
    if (c1 > c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<=(const Complex& c1, const double m)
{
    if (c1 > m)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<=(const double m, const Complex& c2)
{
    if (m > c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}