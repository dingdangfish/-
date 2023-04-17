#include "../../stack/stack.h"
class Calculator {
public:
	Calculator(string s);
	~Calculator();
	int outPriority(char);      //����ջ�����ȼ�
	int inPriority(char);       //����ջ�����ȼ� 
	bool judgePri(char, char);  //�ж����ȼ� ǰһ��Ϊջ����ţ���һ��Ϊջ�ڷ��� ��ǰ���ں󷵻�1�����򷵻�0 
	int judgePri(char);         //�ж������  ����'#'���� -1������')'���� 0�����򷵻� 1 
	void dealNum(); 	        //��������	
	int calculate();            //���� 
	void setString(string const s) {
		this->s = '#' + s + '#';
		deleteBlank(this->s);   //ɾ���ַ����еĿո� 
	}
private:
	Stack<char>* s_sym;         //����ջ 
	Stack<int>* s_num;          //����ջ 
	string s;
};
Calculator::Calculator(string s) {
	this->s = '#' + s + '#';
	deleteBlank(this->s);
	s_sym = new Stack<char>(MAX);
	s_num = new Stack<int>(MAX);
}
Calculator::~Calculator() {
	delete s_sym;
	delete s_num;
}
int Calculator::outPriority(char symble) {//��ջ�ⲻͬ���ű���ϲ�ͬ���ִ������ȼ�
	switch (symble) {
	case '#':
		return 0;
	case '(':
		return 8;
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 4;
	case '/':
		return 4;
	case '%':
		return 4;
	case '^':
		return 6;
	case ')':
		return 1;
	default:
		throw 1;
	}
}
int Calculator::inPriority(char symble) {//��ջ�ڲ�ͬ���ű���ϲ�ͬ���ִ������ȼ�
	switch (symble) {
	case '#':
		return 0;
	case '(':
		return 1;
	case '+':
		return 3;
	case '-':
		return 3;
	case '*':
		return 5;
	case '/':
		return 5;
	case '%':
		return 5;
	case '^':
		return 7;
	case ')':
		return 8;
	default:
		throw 1;
	}
}
bool Calculator::judgePri(char out, char in) {//�ж����ȼ�
	if (outPriority(out) > inPriority(in))
		return true;
	else
		return false;
}
int Calculator::judgePri(char symble) {//�жϸ��ַ��Ƿ�Ϊ��#���͡�����
	if (symble == '#')
		return -1;
	else if (symble == ')')
		return 0;
	else
		return 1;
}
void Calculator::dealNum() {
	//������ջ�е�ǰ�����������м��㣬����Ż�����ջ������ջ��������Ԫ�� 
	char _temp = 0;
	int dtemp1 = 0;
	int dtemp2 = 0;
	s_sym->Del(_temp);
	s_num->Del(dtemp1);
	s_num->Del(dtemp2);
	switch (_temp) {
	case '+':
		dtemp2 += dtemp1;
		break;
	case '-':
		dtemp2 = dtemp2 - dtemp1;
		break;
	case '*':
		dtemp2 = dtemp2 * dtemp1;
		break;
	case '/':
		if (dtemp1 == 0)
			throw 0;
		else
			dtemp2 = dtemp2 / dtemp1;
		break;
	case '%':
		dtemp2 = dtemp2 % dtemp1;
		break;
	case '^':
		dtemp2 = pow(dtemp2, dtemp1);
		break;
	default:
		throw 1;
	}
	s_num->Add(dtemp2);
}
int Calculator::calculate() {
	for (int i = 0; i < s.size(); i++) {   //�����ַ��� 
		if (isNum(s[i])) {//����ַ����пո�
			int temp = (int)(s[i]) - 48;  //charǿ������ת��Ϊint ascii ����ֵ���� 48 ת��Ϊ��Ӧ����ֵ 
			int _temp = 0;
			if (i > 0 && isNum(s[i - 1])) {
				s_num->Del(_temp);
				temp = _temp * 10 + temp;
			}
			s_num->Add(temp);
		}
		else {
			char temp = s[i];
			if (s_sym->IsEmpty()) {
				s_sym->Add(temp);
			}
			else {
				if (judgePri(temp, s_sym->Top())) {//��ջ�����ȼ���ջ�����ȼ���ʱ��ִ��ջ���������
					s_sym->Add(temp);
				}
				else   if (judgePri(temp) == 1) {          //ջ�����ȼ�С��ջ�����ȼ����Ҳ�Ϊ '#' �� ')' 
					while (!judgePri(temp, s_sym->Top())) { //��ջ�����ȼ���ջ�����ȼ���ʱ��ִ��ջ�ڷ������� 
						dealNum();
					}
					s_sym->Add(temp);

				}
				else if (judgePri(temp) == -1) {
					while (s_sym->Top() != '#') {
						dealNum();
					}
					int result = s_num->Top();
					s_sym->MakeEmpty();
					s_num->MakeEmpty();
					return result;
				}
				else if (judgePri(temp) == 0) {
					while (s_sym->Top() != '(') {
						dealNum();
					}
					s_sym->Del(temp);
				}
			}
		}
	}
}

int main(int argc, char** argv) {
	try {
		string s = "";
		Calculator c(s);//����һ��Ϊ�յļ���������
		while (DONE) {
			s = " ";
			cout << "������ʽ" << endl;
			getline(cin, s);//����������ݴ���s
			c.setString(s);//ɾ���еĿո�
			int result=0;//�����ֵΪ���result,���������ʽ�������������
			result = c.calculate();//�ó����
			cout << c.calculate() << endl;
			//system("pause");//�ó�����ͣһ�£�Ȼ�����������
			//system("cls");
		}
	}
	catch (int i) {//���ֱ�����ж�
		if (i == 0)
			cout << "��������Ϊ0��";
		else if (i == 1)
			cout << "��ʽ��Ч" << endl;
	}
	return 0;
}

