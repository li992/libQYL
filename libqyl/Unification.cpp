#include "Unification.h"

//===============================================================
// Functions for unifier 
void unifier::run() {
	unify(target);
	if (replaceList.front().find("false") == std::string::npos) {
		replaceParams();
		printReplaceList();
		std::cout << "True" << std::endl;
	}
	else {
		std::cout << "False" << std::endl;
	}

}

void unifier::printReplaceList() {
	while (!replaceList.empty()) {
		std::cout << replaceList.front() << std::endl;
		replaceList.pop_front();
	}
}

bool unifier::unify(std::string str) {
	std::list<std::string> tempList, counterList;
	if (isFunction(str))
		tempList = parseFunc(str);
	else
		tempList = parseString(str);

	if (tempList.front() == "") tempList.pop_front();

	int counter = 0;
	counterList = tempList;
	while (!counterList.empty()) {
		counterList.pop_front();
		counter += 1;
	}

	if (counter == 2) {
		std::string firstRule, secondRule;
		firstRule = tempList.front();
		tempList.pop_front();
		secondRule = tempList.front();
		tempList.pop_front();

		std::list<std::string> ruleList;
		if (isFunction(firstRule) && isFunction(secondRule) ){
			doubleFunctionSolution(firstRule, secondRule);
		}
		else if (!isFunction(firstRule)) {
			std::string replaceStr = firstRule + " = " + secondRule;
			replaceList.push_back(replaceStr);
			replaceParams();
		}
		else if (!isFunction(secondRule) && isFunction(firstRule)) {
			std::string replaceStr = secondRule + " = " + firstRule;
			replaceList.push_back(replaceStr);
			replaceParams();
		}
		return true;
	}
	else if (counter == 1) {
		return true;
	}
	else {
		std::cout << "Invalid parameter amounts" << std::endl;
		return false;
	}
}

void unifier::doubleFunctionSolution(std::string firstString, std::string secondString) {
	//check first phrase
	phraseObj firstPhrase, secondPhrase;

	firstPhrase.setObj(firstString, isFunction(firstString));
	secondPhrase.setObj(secondString, isFunction(secondString));

	firstPhrase.analyzePhrase();
	secondPhrase.analyzePhrase();

	if (firstPhrase.getNumOfParams() == secondPhrase.getNumOfParams()) {
		//std::cout << "here stop" << std::endl;
		if (firstPhrase.getNumOfParams() == 1) {
			if (isFunction(firstPhrase.getPhrase()) && isFunction(secondPhrase.getPhrase())) {
				doubleFunctionSolution(firstPhrase.getPhrase(), secondPhrase.getPhrase());
			}
			else if (isFunction(firstPhrase.getPhrase()) && !isFunction(secondPhrase.getPhrase())) {
				replaceList.push_back(firstPhrase.getPhrase() + " = " + secondPhrase.getPhrase());
			}
			else if (!isFunction(firstPhrase.getPhrase()) && isFunction(secondPhrase.getPhrase())) {
				replaceList.push_back(secondPhrase.getPhrase() + " = " + firstPhrase.getPhrase());
			}
			else {
				replaceList.push_back(firstPhrase.getPhrase() + " = " + secondPhrase.getPhrase());
			}
		}
		else if (firstPhrase.getNumOfParams() == 2) {
			//std::cout << "it goes here" << std::endl;
			std::list<std::string> firstList = firstPhrase.getList();
			std::list<std::string> secondList = secondPhrase.getList();
			while (!firstList.empty()) {
				std::string first = firstList.front();
				std::string second = secondList.front();

				firstList.pop_front();
				secondList.pop_front();

				if ((isFunction(first) && !isFunction(second)) || (isFunction(second) && !isFunction(first)))
					doubleFunctionSolution("f(" + first + ")", "f(" + second + ")");
				else
					doubleFunctionSolution(first, second);
			}
		}
	}
	else {
		replaceList.clear();
		replaceList.push_front("false - invliad number of parameters");
	}
}

bool unifier::isFunction(std::string str) {
	bool bracket = false;
	bool comma = false;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(') {
			if (comma == true) return false;
			else if (comma == false) return true;
		}
		if (str[i] == ',') comma = true;

	}
	return false;
}

std::list<std::string> unifier::parseFunc(std::string str) {
	std::list<std::string> tempList;
	tempList.clear();
	std::string tempStr;
	// openBracketCounter: to check how many left bracket is open while reading the string
	// pos: the current position of reading head
	// phraseBeginPos: the position of phrase started
	// phraseEndPos: the position of phrase ended
	int openBracketCounter = 0, pos = 0, phraseBeginPos = 0, phraseEndPos = 0;
	while (pos < str.length()) {
		if (str[pos] == '(') openBracketCounter++;
		if (str[pos] == ')') openBracketCounter--;

		if (str[pos] == '(' && openBracketCounter == 1) phraseBeginPos = pos+1;
		if (str[pos] == ',' && openBracketCounter == 1) {
			phraseEndPos = pos;
			tempStr = str.substr(phraseBeginPos, phraseEndPos - phraseBeginPos);
			tempList.push_back(tempStr);
			phraseBeginPos = pos+1;
		}
		if (openBracketCounter == 0) {
			phraseEndPos = pos;
			tempStr = str.substr(phraseBeginPos, phraseEndPos - phraseBeginPos);
			tempList.push_back(tempStr);
		}
		pos++;
	}
	return tempList;
}

std::list<std::string> unifier::parseString(std::string str) {
	std::list<std::string> tempList;
	std::string tempStr;
	// openBracketCounter: to check how many left bracket is open while reading the string
	// pos: the current position of reading head
	// phraseBeginPos: the position of phrase started
	// phraseEndPos: the position of phrase ended
	int openBracketCounter = 0, pos = 0, phraseBeginPos = 0, phraseEndPos = 0;
	while (pos < str.length()) {
		if (str[pos] == '(') openBracketCounter++;
		if (str[pos] == ')') openBracketCounter--;

		if (str[pos] == ',' && openBracketCounter == 0) {
			phraseEndPos = pos;
			tempStr = str.substr(phraseBeginPos, phraseEndPos - phraseBeginPos);
			tempList.push_back(tempStr);
			phraseBeginPos = pos+1;
		}
		if (str[pos] == ')' && openBracketCounter == 0) {
			phraseEndPos = pos;
			tempStr = str.substr(phraseBeginPos, phraseEndPos - phraseBeginPos);
			tempList.push_back(tempStr);
		}
		pos++;
	}
	return tempList;
}

void unifier::replaceParams() {
	std::list<std::string> tempList = replaceList, outList, resultList;

	// this for loop is mainly to ask the program to mandatory check n times 
	for (int i = 0; i < replaceList.size(); i++) {
		outList.clear();
		std::string tempStr = tempList.front();
		tempList.pop_front();
		tempList.push_back(tempStr);
		resultList.push_back(tempStr);
		std::string left, right;
		std::size_t found = tempStr.find('=');
		if (found != std::string::npos) {
			left = tempStr.substr(0, found - 2);
			right = tempStr.substr(found + 2, tempStr.length() - found - 3);
			std::list<std::string> tempList2 = tempList;
			// this while loop will check each replacable string against with the left and right value of current string
			while (!tempList2.empty()) {
				std::string str = tempList2.front();
				tempList2.pop_front();
				if (str != tempStr) {
					std::size_t tempFound = str.find('=');
					if (tempFound != std::string::npos) {
						if (str.substr(0, tempFound - 2).find(right) != std::string::npos) {
							str.replace(str.find(right), right.length(), left);
						}
						outList.push_back(str);
					}
				}
				else
					outList.push_back(str);
			}
			resultList = outList;
			tempList = outList;
		}
		else {
			std::cout << "Invliad replacable string in list!" << std::endl;
			break;
		}
	}
	replaceList = resultList;
}

// ========================================================================================
// Class phraseObj functions
std::string phraseObj::getType() {
	if (type == 0) return "function";
	else if (type == 1) return "phrase";
	else return "unknown";
}

int phraseObj::getNumOfParams() {
	return numOfParams;
}

std::string phraseObj::getPhrase() {
	return phrase;
}

void phraseObj::setType(int typeInt) {
	type = typeInt;
	return;
}

void phraseObj::setType(std::string typeStr) {
	if (typeStr == "function") type = 0;
	else if (typeStr == "phrase") type = 1;
	else type = -1;
	return;
}

void phraseObj::setNumOfParams(int num) {
	numOfParams = num;
	return;
}

void phraseObj::setPhrase(std::string str) {
	phrase = str;
	return;
}

phraseObj::phraseObj(int typeInt, int num, std::string str) {
	type = typeInt;
	numOfParams = num;
	phrase = str;
}
phraseObj::phraseObj() {
	type = -1;
	numOfParams = 0;
	phrase = "";
}

void phraseObj::analyzePhrase() {
	std::list<std::string> tempList;
	tempList.clear();
	std::string tempStr;
	// openBracketCounter: to check how many left bracket is open while reading the string
	// pos: the current position of reading head
	// phraseBeginPos: the position of phrase started
	// phraseEndPos: the position of phrase ended
	int openBracketCounter = 0, pos = 0, phraseBeginPos = 0, phraseEndPos = 0;
	while (pos < phrase.length()) {
		if (phrase[pos] == '(') openBracketCounter++;
		if (phrase[pos] == ')') openBracketCounter--;
		if (phrase[pos] == ',' && openBracketCounter == 0) {
			phraseEndPos = pos;
			tempStr = phrase.substr(phraseBeginPos, phraseEndPos - phraseBeginPos);
			tempList.push_back(tempStr);
			phraseBeginPos = pos + 1;
		}
		pos++;
	}
	phraseList = tempList;

	int counter = 0;
	while (!tempList.empty()) {
		tempList.pop_front();
		counter += 1;
	}
	
	numOfParams = counter;
	return;
}

void phraseObj::setObj(std::string phraseStr, bool isfunction) {
	if (isfunction) {
		setType(0);
		setPhrase(phraseStr.substr(phraseStr.find('(')+1, phraseStr.length() - phraseStr.find('(') -2) + ",");
		//setPhrase(phraseStr + ",");
	}
	else {
		setType(1);
		setPhrase(phraseStr + ",");
	}
	return;
}