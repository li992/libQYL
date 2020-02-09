//  Author: li992
//	Date: 2020/02/08
//	Program purpose: Achieve unification in c++
//  Test Cases:	f(f(f(X,Y),X),f(f(V,U),g(U,Y)))
//				f(X,a)
//				f(a,h(X))
//				f(f(a),f(b))
//				f(f(a,b),f(c))

#include <iostream>
#include <string>
#include "Unification.h"

int main(int argc, char* argv[]) {
	std::string input;
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			input += argv[i];
		}
	}
	else {
		std::cout << "Please Enter the string to unify: ";
		std::getline(std::cin, input);
	}
	//std::cout << input << std::endl;

	// This part is to change every string into the format of f(A,B) where A,B can be either variable or functions
	if (input.find('(') == 0) input = "f" + input;
	if ((input.find('(') != 0) && (input.find('(')!=std::string::npos)) {
		input.replace(0, input.substr(0, input.find('(')).length(), "f");
	}
	
	// unification calls
	unifier unification;
	unification.setTargetString(input);
	unification.run();
	return 0;
}
