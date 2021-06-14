#include <iostream>
#include <string>
#include "MyStack.h"
using namespace std;
string infix2suffix(const string&);
int compute(const string&);

int main() {
	int ans = compute("3+(5-3)*3-4/2-1-3+(5-8/4+1)/2");	// ������С��������������������
	cout << ans;
	return 0;
}

string infix2suffix(const string& infix) {
	MyStack<char> s;
	string suffix = "";
	string::const_iterator itr = infix.cbegin();
	while (itr != infix.cend()) {
		char temp = (*itr);
		if (temp >= '0' && temp <= '9')	// ����
			suffix += temp;
		else if (temp == '(')	// ������
			s.push(temp);
		else if (temp == ')') {	// ������
			while (!s.isEmpty() && s.top() != '(') {
				suffix += s.top();
				s.pop();
			}
			s.pop();
		}
		else {	// �������Ӽ��˳�
			if (temp == '+' || temp == '-') {
				while (!s.isEmpty() && s.top() != '(') {	// ��������ѹ��ջ�����ȼ���Ϊ���
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
		if (temp >= '0' && temp <= '9')	// ����
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