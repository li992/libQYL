#include<stdlib.h>
#include<iostream>
#include<list>
#include<string.h>
#include <algorithm> 
#include <cctype>
#include <locale>

class unifier {
private:
	std::string target; // the input string from user
	std::list<std::string> replaceList;	// the list to store replacable strings
public:
	//setters and getters
	void setTargetString(std::string str) { target = str; }
	std::string getTargetString() { return target; }

	void run();	// it will start the unification steps on target string
	void printReplaceList();
	bool unify(std::string);	//initialize the step and have a quickly checking of unification, it handles the format f(A,B) into g(A),g(B)
	std::list<std::string> parseFunc(std::string);	// parse the function in format f(A,B)
	std::list<std::string> parseString(std::string);	// parse the string in format A,B
	bool isFunction(std::string);	//to check if the passing string is a function
	void replaceParams();	// repeat converting existing replacable string in list
	void doubleFunctionSolution(std::string, std::string);	// it handles unification in format of f(A),f(B)

	// constructors
	unifier() { target = ""; }
	unifier(std::string str) { target = str; }
};


//Phrase Object contains 3 properties:
// 1. object type: function(0) or variable(1)
// 2. number of parameters
// 3. phrase: whole phrase (string) or phrase parsed into paramters (list)
class phraseObj {
private:
	int type;
	int numOfParams;
	std::string phrase;
	std::list<std::string> phraseList;

public:
	// setters and getters
	std::string getType();
	int getNumOfParams();
	std::string getPhrase();
	std::list<std::string> getList() { return phraseList; }
	void setType(std::string);
	void setType(int);
	void setNumOfParams(int);
	void setPhrase(std::string);
	//constructors
	phraseObj(int, int, std::string);
	phraseObj();

	// analyzePhrase is to parse the phrase into paramters
	void analyzePhrase();
	// setObj will ask for phrase string and a boolean variable present if the phrase is a function or not, then automatically assign property 1 and 2
	void setObj(std::string, bool);
};
