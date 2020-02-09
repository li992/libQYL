#include "InfixPostFixConvertorTree.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

treeNodes::treeNodes() {
	left = right = parent = nullptr;
}

treeNodes::~treeNodes() {
	delete left, right;
}

void treeNodes::saveValue(string token) {
	value = token;
	return;
}

string treeNodes::getValue() {
	return value;
}

void treeNodes::setLeft(treeNodes* Lptr) {
	left = Lptr;
	return;
}

void treeNodes::setRight(treeNodes* Rptr) {
	right = Rptr;
	return;
}

void treeNodes::setParent(treeNodes* Pptr) {
	parent = Pptr;
	return;
}