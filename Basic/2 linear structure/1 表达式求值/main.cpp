#include <iostream>
#include <string>
#include "MyStack.h"
using namespace std;
string infix2suffix(const string&);
int compute(const string&);

int main() {
	int ans = compute("3+(5-3)*3-4/2-1-3+(5-8/4+1)/2");	// 不能有小数产生，否则会运算错误
	cout << ans;
	return 0;
}

string infix2suffix(const string& infix) {
	MyStack<char> s;
	string suffix = "";
	string::const_iterator itr = infix.cbegin();
	while (itr != infix.cend()) {
		char temp = (*itr);
		if (temp >= '0' && temp <= '9')	// 数字
			suffix += temp;
		else if (temp == '(')	// 左括号
			s.push(temp);
		else if (temp == ')') {	// 右括号
			while (!s.isEmpty() && s.top() != '(') {
				suffix += s.top();
				s.pop();
			}
			s.pop();
		}
		else {	// 其他：加减乘除
			if (temp == '+' || temp == '-') {
				while (!s.isEmpty() && s.top() != '(') {	// 左括号在压入栈后，优先级变为最低
					suffix += s.top();
					s.pop();
				}
				s.push(temp);
			}
			else {
				while (!s.isEmpty() && s.top() != '(' && s.top() != '+' && s.top() != '-') {
					suffix += s.top();
					s.pop();
				}
				s.push(temp);
			}
		}
		++itr;
	}
	while (!s.isEmpty()) {
		suffix += s.top();
		s.pop();
	}
	return suffix;
}

int compute(const string& infix) {
	string suffix = infix2suffix(infix);
	int l, r, t = 0;
	MyStack<char> s;
	string::const_iterator itr = suffix.cbegin();
	while (itr != suffix.cend()) {
		char temp = (*itr);
		if (temp >= '0' && temp <= '9')	// 数字
			s.push(temp);
		else {
			r = s.top() - 48;
			s.pop();
			l = s.top() - 48;
			s.pop();
			switch (temp)
			{
			case '+':
				t = l + r;
				break;
			case '-':
				t = l - r;
				break;
			case '*':
				t = l * r;
				break;
			case '/':
				t = l / r;
				break;
			}
			s.push(t + 48);
		}
		++itr;
	}
	return t;
}