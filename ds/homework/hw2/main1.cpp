#include "../../stack/stack.h"
class Calculator {
public:
	Calculator(string s);
	~Calculator();
	int outPriority(char);      //返回栈外优先级
	int inPriority(char);       //返回栈内优先级 
	bool judgePri(char, char);  //判断优先级 前一个为栈外符号，后一个为栈内符号 若前大于后返回1，否则返回0 
	int judgePri(char);         //判断运算符  若是'#'返回 -1，若是')'返回 0，否则返回 1 
	void dealNum(); 	        //处理数据	
	int calculate();            //计算 
	void setString(string const s) {
		this->s = '#' + s + '#';
		deleteBlank(this->s);   //删除字符串中的空格 
	}
private:
	Stack<char>* s_sym;         //符号栈 
	Stack<int>* s_num;          //数据栈 
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
int Calculator::outPriority(char symble) {//对栈外不同符号标记上不同数字代表优先级
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
int Calculator::inPriority(char symble) {//对栈内不同符号标记上不同数字代表优先级
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
bool Calculator::judgePri(char out, char in) {//判断优先级
	if (outPriority(out) > inPriority(in))
		return true;
	else
		return false;
}
int Calculator::judgePri(char symble) {//判断该字符是否为‘#’和‘）’
	if (symble == '#')
		return -1;
	else if (symble == ')')
		return 0;
	else
		return 1;
}
void Calculator::dealNum() {
	//将数据栈中的前两个弹出进行计算，结果放回数据栈，符号栈弹出顶部元素 
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
	for (int i = 0; i < s.size(); i++) {   //遍历字符串 
		if (isNum(s[i])) {//清空字符串中空格
			int temp = (int)(s[i]) - 48;  //char强制类型转换为int ascii 码数值，减 48 转换为对应整数值 
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
				if (judgePri(temp, s_sym->Top())) {//当栈外优先级比栈内优先级高时，执行栈外符号运算
					s_sym->Add(temp);
				}
				else   if (judgePri(temp) == 1) {          //栈外优先级小于栈内优先级，且不为 '#' 和 ')' 
					while (!judgePri(temp, s_sym->Top())) { //当栈外优先级比栈内优先级低时，执行栈内符号运算 
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
		Calculator c(s);//定义一个为空的计算器类型
		while (DONE) {
			s = " ";
			cout << "输入算式" << endl;
			getline(cin, s);//将输入的数据传给s
			c.setString(s);//删除中的空格
			int result=0;//定义初值为零的result,避免输入格式错误而出现乱码
			result = c.calculate();//得出结果
			cout << c.calculate() << endl;
			//system("pause");//让程序暂停一下，然后按任意键继续
			//system("cls");
		}
	}
	catch (int i) {//两种报错的判定
		if (i == 0)
			cout << "除数不能为0！";
		else if (i == 1)
			cout << "该式无效" << endl;
	}
	return 0;
}

