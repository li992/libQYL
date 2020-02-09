#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string>
#include<list>

// CFG stands for Context Free Grammer
class CFG {
private:
	std::list<std::string> CfgRules;
	std::list<std::string> CfgRulesInChomsky;
	std::list<char> usedChar;
	std::list<char> validChar;

	std::string tolower(std::string);		// this will return a string with all character in lower case
	std::string delimeterReplace(std::string);	// replace -> and | into , for further operation
	std::list<std::string> delimeterConvertBack(std::list<std::string>);	// replace all strings in a list back to -> and | form
	std::list<std::string> parse(std::string);	// parse string by spliting , and store parsed string into a string list
	std::string removeEmptyString(std::string, char);	// this will take _ off from a string and return string satisfies no _ symbol
	std::string findReplaceStr(std::string);	// This will find a replacable string for single nonterminal
	std::string getReplacedString(std::list<std::string>, std::list<std::string>, std::string);	// this will return a pattern that already been set, for stepFour
	std::string getByPattern(char, std::list<std::string>, std::list<std::string>);	// same thing with getReplacedString function but this is for stepFive

	bool isNonterminal(char);	// check if a symbol is nonterminal or not
	bool isTerminal(char);		// check if a symbol is terminal or not
	bool emptyStrContained();	// check if there is still a _ in states that are not a start state
	bool notInList(std::list<char>, char);	// check if a character is in a list or not
	bool patternReplacedBefore(std::list<std::string>, std::list<std::string>, std::string);	// replacable pattern checking for stepFour
	bool replacingPatternExist(char, std::list<std::string>, std::list<std::string>);	// replacable pattern checking for stepFive

	void setValidChar(); //set usable nonterminals
	void setUsedChar();	// check and set nonterminals that are already been used

	// converting steps
	void stepOne();
	void stepTwo();
	void stepThree();
	void stepFour();
	void stepFive();

public:
	void setCfgRules(std::list<std::string> list) { CfgRules = list; CfgRulesInChomsky = list; setUsedChar();  setValidChar(); return; }
	std::list<std::string> getcfgRules() { return CfgRules; }
	std::list<std::string> getCfgRulesInChomsky() { return CfgRulesInChomsky; }

	void readGrammer();
	void convertToChomsky();
	void printChomsky();

	CFG();
	~CFG() {};
};