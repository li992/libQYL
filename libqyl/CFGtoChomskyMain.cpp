//  author: li992
//	Date: 2019/10/31
//	Program purpose: the pupose of this program is to convert a CFG into Chomsky Normal Form

#include <iostream>
#include "Chomsky.h"

void testSampleOne();
void testSampleTwo();
void testSampleThree();
void testSampleFour();
void testSampleFive();

//int main()
//{
//	int option;
//	std::cout << "This Program will Convert a CFG rule into Chomsky Normal Form\n";
//	std::cout << "Please select input options:\n";
//	std::cout << "	1) mannually enter CFG rules\n";
//	std::cout << "	2) check program preset CFG rules\n";
//	std::cout << "Enter:";
//	std::cin >> option;
//	while (option != 1 && option != 2) {
//		std::cout << "Invalid option, please re-enter:";
//		std::cin >> option;
//	}
//
//	if (option == 2) {
//		testSampleOne();
//		std::cout << std::endl << std::endl;
//		testSampleTwo();
//		std::cout << std::endl << std::endl;
//		testSampleThree();
//		std::cout << std::endl << std::endl;
//		testSampleFour();
//		std::cout << std::endl << std::endl;
//		testSampleFive();
//		return 0;
//	}
//	else {
//		CFG* ptr = new CFG();
//		ptr->readGrammer();
//		ptr->convertToChomsky();
//		ptr->printChomsky();
//		delete ptr;
//		return 1;
//	}
//}

void testSampleOne() {
	CFG* ptr = new CFG();
	std::list<std::string> tempCFGRules;
	tempCFGRules.clear();
	tempCFGRules.push_back("S,0S1,SS,_");
	ptr->setCfgRules(tempCFGRules);
	ptr->convertToChomsky();
	ptr->printChomsky();
	delete ptr;
}

void testSampleTwo() {
	CFG* ptr = new CFG();
	std::list<std::string> tempCFGRules;
	tempCFGRules.clear();
	tempCFGRules.push_front("B,b,_");
	tempCFGRules.push_front("A,B,S");
	tempCFGRules.push_front("S,ASA,aB");
	ptr->setCfgRules(tempCFGRules);
	ptr->convertToChomsky();
	ptr->printChomsky();
	delete ptr;
}

void testSampleThree() {
	CFG* ptr = new CFG();
	std::list<std::string> tempCFGRules;
	tempCFGRules.clear();
	tempCFGRules.push_back("S,_,aS,aSbS");
	ptr->setCfgRules(tempCFGRules);
	ptr->convertToChomsky();
	ptr->printChomsky();
	delete ptr;
}

void testSampleFour() {
	CFG* ptr = new CFG();
	std::list<std::string> tempCFGRules;
	tempCFGRules.clear();
	tempCFGRules.push_back("S,0S,1S,01011A");
	tempCFGRules.push_back("A,_,0A,1A");
	ptr->setCfgRules(tempCFGRules);
	ptr->convertToChomsky();
	ptr->printChomsky();
	delete ptr;
}

void testSampleFive() {
	CFG* ptr = new CFG();
	std::list<std::string> tempCFGRules;
	tempCFGRules.clear();
	tempCFGRules.push_back("S,_,0,1,0S0,1S1");
	ptr->setCfgRules(tempCFGRules);
	ptr->convertToChomsky();
	ptr->printChomsky();
	delete ptr;
}
// author: li992