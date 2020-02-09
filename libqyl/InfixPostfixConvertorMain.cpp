// Author: li992
#include "InfixPostfixConvertor.h"
#include <iostream>
#include <string>
using namespace std;

bool checkSpace(char);
bool checkOperator(char);
bool checkNum(char);
bool GoFirst(char, char);
int getPrecedence(char);

//int main()
//{
//	stack<char> tempStack;
//
//	string input, output;
//	char temp;
//	cout << "Please enter your experssion:";
//	getline(cin, input);
//
//	for (int i = 0; i < input.length(); i++) {
//		if (checkSpace(input[i])) {
//			goto end;
//		}
//		else if (checkNum(input[i])) {
//			output += input[i];
//			output += " ";
//		}
//		else if (checkOperator(input[1])) {
//			while (!tempStack.isEmpty() && tempStack.getTop() != '(' && GoFirst(tempStack.getTop(), input[i])) {
//				output += tempStack.getTop();
//				tempStack.pop(temp);
//				output += temp;
//				output += " ";
//			}
//			tempStack.push(input[i]);
//		}
//		else if (input[i] == '(') {
//			tempStack.push(input[i]);
//		}
//		else if (input[i] == ')') {
//			while (!tempStack.isEmpty() && tempStack.getTop() != '(') {
//				output += tempStack.getTop();
//				tempStack.pop(temp);
//				output += temp;
//				output += " ";
//			}
//			tempStack.pop(temp);
//			output += temp;
//			output += " ";
//		}
//
//		while (!tempStack.isEmpty()) {
//			output += tempStack.getTop();
//			tempStack.pop(temp);
//			output += temp;
//			output += " ";
//		}
//
//	end:;
//	}
//
//	cout << "Postfix version is: " << output << endl;
//
//	return 0;
//}

bool checkSpace(char a) {
	if (a == ' ')
		return true;
	return false;
}
bool checkOperator(char a) {
	if (a == '+' || a == '-' || a == '*' || a == '/')
		return true;
	return false;
}

bool checkNum(char a) {
	if (a >= '0' && a <= '9')
		return true;
	return false;
}

bool GoFirst(char top, char input) {
	int topPrecedence = getPrecedence(top);
	int inputPrecedence = getPrecedence(input);
	return topPrecedence > inputPrecedence;
}

int getPrecedence(char a) {
	switch (a) {
	case '-':
	case'+': return 1;
	case'*':
	case'/':return 2;
	default:return 0;
	}
}