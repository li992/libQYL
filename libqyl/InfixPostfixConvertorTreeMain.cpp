// author: li992

#include "InfixPostFixConvertorTree.h"
#include <iostream>
#include <string>
#include <stack>
#include <sstream>	// for string tokenizing
#include <vector>	// for tokenized string storage
using namespace std;

// Infix to Postfix convertor
bool checkOperator(string);
bool checkNum(string);
bool GoFirst(char, char);
int getPrecedence(char);
string InfixToPostfix(string);

// Tree builder functions
//void checkParentLeft(treeNodes*, treeNodes*, string);
void saveRight(treeNodes*, string);	// save right child
void saveLeft(treeNodes*, string);	// save left child
bool checkLeft(treeNodes*&);		// check if there is empty pointer left on each node's left
bool checkRight(treeNodes*&);		// check if there is empty pointer left on each node's right

// Print functions
void printTreeInfix(treeNodes*);
void printTreePrefix(treeNodes*);
void printTreePostfix(treeNodes*);
string printLeft(treeNodes*);
string printRoot(treeNodes*);
string printRight(treeNodes*);

/********************************************************************** main function starts **********************************************************************************************/
//
//int main()
//{
//	// user selection for input method
//	char selection;
//	cout << "Welcome to use infix/postfix convertor, please select your input method:" << endl << "1) infix" << endl << "2) postfix" << endl << "0) quit" << endl
//		<< "Note: Please enter the number in front of each method" << endl << "Your selection: ";
//	cin >> selection;
//	while (selection != '1' && selection != '2' && selection != '0') {
//		cout << "Not a valid input, please reselect: ";
//		cin >> selection;
//	}
//
//	cin.ignore();	// ignore the previous input line from reading by getline 
//
//	// infix to postfix conversion main functions
//	string input, output;
//	cout << "Please enter your experssion:";
//	getline(cin, input);
//
//	// jumping list
//	switch (selection) {
//	case '1':goto infix; break;
//	case '2':goto postfix; break;
//	case '0':
//	default: return 0;
//	}
//
//infix:;
//	try {
//		output = InfixToPostfix(input);
//		cout << "Postfix version is: " << output << endl;
//	}
//	catch (const char* msg) {
//		cerr << msg << endl;
//	}
//postfix:;
//	if (selection == '2') {
//		output = input;
//	}
//	// the following code is to tokenize the postfix string
//	vector <string> sets;
//	istringstream iss(output);
//	string token;
//	int i = 0;
//	while (getline(iss, token, ' ')) {
//		sets.push_back(token);
//	}
//
//	// The fllowing part is for type of expression detection, since I don't have prefix handling, I will use user choice input at beginning
//
//	//if (sets[0][0] >= '0'&&sets[0][0] <= '9') {
//	//	if (sets[sets.size() - 1][0] >= '0' && sets[sets.size() - 1][0] <= '9') {
//	//		cout << "Your input is Infix version!" << endl;
//	//	}
//	//	else {
//	//		cout << "Your input is Postfix version!" << endl;
//	//	}
//	//}
//	//else {
//	//	cout << "Your input is Prefix version!" << endl;
//	//}
//
//	// set up root of the tree and current pointer to operate
//	treeNodes* head = new treeNodes;
//	treeNodes* current = head;
//	// treeNodes* previous = current; // this used to be a testing pointer
//	current->saveValue(sets[sets.size() - 1]);
//
//	// the following code is for tree building
//	for (int i = sets.size() - 2; i >= 0; i--) {
//		if (sets[i][0] >= '0' && sets[i][0] <= '9') {
//			if (current->getValue() == "") {
//				current->saveValue(sets[i]);
//				current = current->getParent();
//			}
//			else {
//				if (current->getRight() != NULL) {
//					if (checkLeft(current)) {
//						saveLeft(current, sets[i]);
//					}
//					else {
//						cout << "tree build unsuccessfully";
//					}
//				}
//				else {
//					saveRight(current, sets[i]);
//				}
//			}
//		}
//		else {
//			if (checkRight(current))
//			{
//				saveRight(current, sets[i]);
//				current = current->getRight();
//			}
//			else {
//				if (checkLeft(current)) {
//					saveLeft(current, sets[i]);
//					current = current->getLeft();
//				}
//				else {
//					cout << "tree build unsuccessfully";
//				}
//			}
//
//		}
//	}
//
//	// initial the root pointer
//	while (current->getParent() != NULL) {
//		current = current->getParent();
//	}
//	head = current;
//
//	// output method user input
//	char outputMethod;
//	cout << endl;
//	cout << "Please enter a method of output:" << endl << "1) Infix" << endl << "2) Prefix" << endl << "3) Postfix" << endl << "0) End" << endl << "Please enter your selection: ";
//	cin >> outputMethod;
//	while (true) {
//		switch (outputMethod) {
//		case '1':
//			printTreeInfix(head);
//			cout << endl << endl;
//			break;
//		case '2':
//			printTreePrefix(head);
//			cout << endl << endl;
//			break;
//		case '3':
//			printTreePostfix(head);
//			cout << endl << endl;
//			break;
//		case '0':return 0; break;
//		default:cout << "Invalid input" << endl;
//		}
//		cout << "Please enter a method of output:" << endl << "1) Infix" << endl << "2) Prefix" << endl << "3) Postfix" << endl << "0) End" << endl << "Please enter your selection: ";
//		cin >> outputMethod;
//	}
//	return 0;
//}
//
//


/*********************************************************************** functions start from here ***************************************************************************************************************/
// author: li992
string InfixToPostfix(string input) {  // main function to do the conversion from infix to postfix by using stack method
	stack<char> tempStack;
	string output;
	istringstream iss(input);
	string token;
	while (getline(iss, token, ' ')) {	// this is the part for string tokenizing, which will accept mutiple digit or negetive number input
		if (checkNum(token)) {
			output += token;
			output += " ";
		}
		else if (checkOperator(token)) {
			while (!tempStack.empty() && tempStack.top() != '(' && GoFirst(tempStack.top(), token[0])) {
				output += tempStack.top();
				output += " ";
				tempStack.pop();
			}
			tempStack.push(token[0]);
		}
		else if (token[0] == '(') {
			tempStack.push(token[0]);
		}
		else if (token[0] == ')') {
			while (!tempStack.empty() && tempStack.top() != '(') {
				output += tempStack.top();
				output += " ";
				tempStack.pop();
			}
			tempStack.pop();
		}
		else {
			throw "Unknown character for calculation: " + token;
		}
	}
	while (!tempStack.empty()) {
		output += tempStack.top();
		output += " ";
		tempStack.pop();
	}

	return output;
}

bool checkOperator(string a) { // to check if this string is an operator
	bool check = false;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/')
			check = true;
		else
			check = false;
	}
	if (a.length() > 1) { check = false; } // no operator can be longer than 1 char space
	return check;
}

bool checkNum(string a) {		// check if this string is a number
	bool check = false;
	for (int i = 0; i < a.length(); i++) {
		if (a[i] >= '0' && a[i] <= '9')
			check = true;
		else
			check = false;
	}
	return check;
}

bool GoFirst(char top, char input) {		// check if an operator has higher precedency
	int topPrecedence = getPrecedence(top);
	int inputPrecedence = getPrecedence(input);
	return topPrecedence > inputPrecedence;
}

int getPrecedence(char a) {	// different operator has different precedence
	switch (a) {
	case '-':
	case'+': return 1;
	case'*':
	case'/':return 2;
	default:return 0;
	}
}

//void checkParentLeft(treeNodes* ptr, treeNodes* head, string value) {
//	if (ptr->getLeft() == NULL) {
//		ptr->setLeft(new treeNodes);
//		ptr->getLeft()->saveValue(value);
//	}
//	else {
//		if (ptr != head) {
//			checkParentLeft(ptr->getParent(),head, value);
//		}
//		else {
//			throw "extra number exists!";
//		}
//	}
//	return;
//}

void saveRight(treeNodes* ptr, string value) {		// save the right child to current ptr
	ptr->setRight(new treeNodes);
	ptr->getRight()->setParent(ptr);
	ptr->getRight()->saveValue(value);
}

void saveLeft(treeNodes* ptr, string value) {		// save the left child to current ptr
	ptr->setLeft(new treeNodes);
	ptr->getLeft()->setParent(ptr);
	ptr->getLeft()->saveValue(value);
}

bool checkLeft(treeNodes*& t) {
	if (t->getValue()[0] >= '0' && t->getValue()[0] <= '9') {
		t = t->getParent();
		checkLeft(t);
	}
	else {
		if (t->getLeft() == NULL) {				// when current ptr has a left child of null, which means it can be used to store value
			return true;
		}
		else {
			if (t->getParent() == NULL) {		// if it is already the root of the tree return false
				return false;
			}
			t = t->getParent();
			checkLeft(t);			// keep checking
		}
	}
}

bool checkRight(treeNodes*& t) {
	if (t->getRight() != NULL) {
		t = t->getRight();
		checkRight(t);			// if right child is not null, keep going to reach the deepest right child
	}
	else {
		if (t->getValue()[0] >= '0' && t->getValue()[0] <= '9') {
			return false;			// when detect the right deepest value is a number
		}
		else {
			return true;			// when detect the right deepest value is still a operator
		}
	}
}


// these three functions below are all printing methods
// author: li992
void printTreeInfix(treeNodes* t) {
	if (t->getLeft() == nullptr && t->getRight() == nullptr) {
		cout << t->getValue() << " ";
	}
	else {
		cout << "(";
		printTreeInfix(t->getLeft());
		cout << ")";
		cout << t->getValue() << " ";
		cout << "(";
		printTreeInfix(t->getRight());
		cout << ")";
	}
}
void printTreePrefix(treeNodes* t) {
	if (t->getLeft() == nullptr && t->getRight() == nullptr) {
		cout << t->getValue() << " ";
	}
	else {
		cout << t->getValue() << " ";
		printTreePrefix(t->getLeft());
		printTreePrefix(t->getRight());
	}
}
void printTreePostfix(treeNodes* t) {
	if (t->getLeft() == nullptr && t->getRight() == nullptr) {
		cout << t->getValue() << " ";
	}
	else {
		printTreePostfix(t->getLeft());
		printTreePostfix(t->getRight());
		cout << t->getValue() << " ";
	}
}
