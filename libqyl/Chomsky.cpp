#include"Chomsky.h"

CFG::CFG() {
	CfgRules.clear();
	CfgRulesInChomsky.clear();
	usedChar.clear();
	validChar.clear();
}

void CFG::printChomsky() {
	std::list<std::string> currCFG = CfgRules;
	std::list<std::string> temp = CfgRulesInChomsky;
	std::list<std::string> sortedList;

	std::cout << "Original CFG Rules:\n";
	sortedList.clear();
	sortedList = delimeterConvertBack(CfgRules);
	while (!currCFG.empty()) {
		std::cout << "	" << currCFG.front() << std::endl;
		currCFG.pop_front();
	}

	std::cout << "CFG Rules in Chomsky Normal Form:\n";
	sortedList.clear();
	sortedList = delimeterConvertBack(CfgRulesInChomsky);
	while (!sortedList.empty()) {
		if(sortedList.front().length()!=1)
			std::cout << "	" << sortedList.front() << std::endl;
		sortedList.pop_front();
	}
}

std::list<std::string> CFG::delimeterConvertBack(std::list<std::string> rules) {
	std::list<std::string> temp;

	while (!rules.empty()) {
		std::string str = rules.front();
		rules.pop_front();
		size_t pos = str.find(',');
		if (pos != std::string::npos) {
			str.replace(pos, 1, "->");
		}
		pos = str.find(',', pos + 1);
		while (pos != std::string::npos) {
			str.replace(pos, 1, "|");
			pos = str.find(',', pos + 1);
		}
		temp.push_back(str);
	}

	return temp;
}

void CFG::readGrammer() {
	std::cout << "Please Enter your rules in following format:\n";
	std::cout << "A->0B|1C\n";
	std::cout << "B->0C|1B\n";
	std::cout << "C->_|0B|1C\n";
	std::cout << "END\n";
	std::cout << "Terminal range: 0-9 and a-z; empty string: _ ; to finish enter: end\n";
	std::cin.ignore();
	while (true) {
		std::cout << "#:";
		std::string str;
		getline(std::cin, str);
		str = delimeterReplace(str);
		if (tolower(str) == "end" ) {
			break;
		}
		CfgRules.push_back(str);
	}
	CfgRulesInChomsky = CfgRules;
	setUsedChar();
	setValidChar();
	return;
}

void CFG::convertToChomsky() {
	try {
		stepOne();
		stepTwo();
		stepThree();
		stepFour();
		stepFive();
	}
	catch(_exception e) {
		throw "error detectd!";
	}

}


// Private Functions
// step one is to create a new head link to previous head
void CFG::stepOne() {
	char usableTerminal = validChar.front();
	validChar.pop_front();
	usedChar.push_back(usableTerminal);
	std::string temp = CfgRules.front();
	//std::cin.ignore();
	std::string newhead;
	newhead.push_back(usableTerminal);
	newhead.push_back(',');
	newhead.push_back(temp[0]);
	CfgRulesInChomsky.push_front(newhead);

	// reset usable nonterminal characters list
	setUsedChar();
	setValidChar();
	return;
}

// step two is to remove empty string(_)
void CFG::stepTwo() {
	// check if there was a empty string, then do it untill no empty string is there
	bool emptyStrDetected = true;;
	while (emptyStrDetected) {
		emptyStrDetected = emptyStrContained();
	}
	return;
}

// check if in cfgRules there exists a empty string
bool CFG::emptyStrContained() {
	std::list<std::string> tempList = CfgRulesInChomsky;
	char targetTerminal = ' ';
	bool returnValue = false;
	char startState = tempList.front()[0];
	// find which nonterminal contains empty string
	while (!tempList.empty()) {
		std::string tempRow = tempList.front();
		tempList.pop_front();
		std::size_t emptyStringPos = tempRow.find('_');
		if (emptyStringPos != std::string::npos) {
			targetTerminal = tempRow[0];
			if (tempRow[0] != startState) {
				returnValue = true;
			}
			break;
		}
	}
	// remove

	// if there is empty string in rule set
	if (targetTerminal != ' ' && returnValue == true) {
		tempList = CfgRulesInChomsky;
		std::list<std::string> newList;
		while (!tempList.empty()) {
			std::string tempRow = tempList.back();
			tempList.pop_back();
			std::string afterRemoval = removeEmptyString(tempRow, targetTerminal);
			newList.push_front(afterRemoval);
		}
		CfgRulesInChomsky = newList;
	}

	return returnValue;
}

// step three: replace all single nontermials by their rule patterns
void CFG::stepThree() {
	std::list<std::string> currList = CfgRulesInChomsky, newList;
	while (!currList.empty()) {
		std::string currRow = currList.back();
		currList.pop_back();
		std::list<std::string> patternList = parse(currRow);
		std::string newRow = patternList.front();
		patternList.pop_front();
		while (!patternList.empty()) {
			std::string currPattern = patternList.front();
			patternList.pop_front();
			if (currPattern.length() == 1 && isNonterminal(currPattern[0])) {
				std::string replaceStr = findReplaceStr(currPattern);
				if (replaceStr == "") {
					std::cout << "Error 100: Chmosky.cpp line 102, no replacable nonterminal can be found!\n";
					return;
				}
				newRow.append("," + replaceStr);
			}
			else newRow.append("," + currPattern);
		}
		newList.push_front(newRow);
	}
	CfgRulesInChomsky = newList;
}

bool CFG::isNonterminal(char target) {
	if ((int)target > 65 && (int)target < 90) {
		return true;
	}
	else return false;
}

std::string CFG::findReplaceStr(std::string pattern) {
	std::list<std::string> currList = CfgRulesInChomsky;
	while (!currList.empty()) {
		std::string currRow = currList.front();
		currList.pop_front();
		if (pattern[0] == currRow[0]) {
			return currRow.erase(0, 2);
		}
	}
	return "";
}

// step four: change all rule pattern that is longer than 3 into smaller pieces
void CFG::stepFour() {
	std::list<std::string> currList = CfgRulesInChomsky, newList;
	std::list<std::string> replacedPatternList, replacedByList;
	newList.clear();
	replacedPatternList.clear();
	replacedByList.clear();

	// deal with currList and put new rows into newList
	while (!currList.empty()) {
		std::string currRow = currList.back();
		currList.pop_back();
		std::list<std::string> patternList = parse(currRow);
		std::string newRow = patternList.front();

		patternList.pop_front();
		while (!patternList.empty()) {
			std::string currPattern = patternList.front();
			patternList.pop_front();
			// deal with pattern and short it to length 2, still currPattern
			while (currPattern.length() >2) {			
				// check if this pattern is already been replaced, if it is then get the replaced version of string to replace it
				if (patternReplacedBefore(replacedPatternList, replacedByList, currPattern)) {
					currPattern = getReplacedString(replacedPatternList, replacedByList, currPattern);
				}
				else {
					replacedPatternList.push_back(currPattern);
					char usableNonterminal = validChar.front();
					validChar.pop_front();
					usedChar.push_back(usableNonterminal);
					// get usable nonterminal, then apply changing

					std::string topTwoChar = "";
					size_t pos = 0;
					char a = currPattern[pos];
					topTwoChar += a;
					pos = 1;
					a = currPattern[pos];
					topTwoChar += a;

					// get the first two char in a pattern, then replace the pattern with the usable char
					size_t topTwoCharPo = currRow.find(topTwoChar);
					std::string x(1, usableNonterminal);
					while (topTwoCharPo != std::string::npos) {
						if(currRow[topTwoCharPo+2]!=','&&currRow[topTwoCharPo+2]!='\0')
							currRow.replace(topTwoCharPo, 2, x);
						topTwoCharPo = currRow.find(topTwoChar, topTwoCharPo + 1);
					}
					

					size_t currPatternPos = currPattern.find(topTwoChar);
					currPattern.replace(currPatternPos, 2, x);
					newList.push_back(x + "," + topTwoChar);
					replacedByList.push_back(currPattern);
				}
			}
			newRow += "," + currPattern;
		}
		newList.push_front(newRow);
	}
	CfgRulesInChomsky = newList;
}

bool CFG::patternReplacedBefore (std::list<std::string> patternList, std::list<std::string> byList, std::string currPattern) {
	while (!patternList.empty()) {
		std::string pattern = patternList.front();
		if (pattern == currPattern) {
			return true;
		}
		patternList.pop_front();
		byList.pop_front();
	}
	return false;
}

std::string CFG::getReplacedString(std::list<std::string> patternList, std::list<std::string> byList, std::string currPattern) {
	while (!patternList.empty() && !byList.empty()) {
		std::string pattern = patternList.front();
		std::string patternReplacedBy = byList.front();
		patternList.pop_front();
		byList.pop_front();
		if (pattern == currPattern) {
			size_t pos = currPattern.find(pattern);
			currPattern.replace(pos, pattern.length(), patternReplacedBy);
			return currPattern;
		}
	}
	return "";
}

// step five: change all terminals within in pattern.length = 2 into nonterminals
void CFG::stepFive() {
	std::list<std::string> currList = CfgRulesInChomsky, newList;
	std::list<std::string> replacedPatternList, replacedByList;
	newList.clear();
	replacedPatternList.clear();
	replacedByList.clear();

	while (!currList.empty()) {
		std::string currRow = currList.back();
		currList.pop_back();
		std::list<std::string> patternList = parse(currRow);
		std::string newRow = patternList.front();

		patternList.pop_front();	// not to deal with lhs nonterminal
		while (!patternList.empty()) {
			std::string currPattern = patternList.front();
			patternList.pop_front();
			if (currPattern.length() == 2) {
				// check if this pattern is already been replaced, if it is then get the replaced version of string to replace it
				// check if on position 0 and position 1 there exist a terminal or if both are terminals
				if (isTerminal(currPattern[0])) {
					// add new rules
					if (replacingPatternExist(currPattern[0], replacedPatternList, replacedByList)) {
						std::string by = getByPattern(currPattern[0], replacedPatternList, replacedByList);
						currPattern.replace(0, 1, by);
					}
					else {
						char usableNonterminal = validChar.front();
						validChar.pop_front();
						usedChar.push_back(usableNonterminal);
						std::string patternStr(1, currPattern[0]);
						replacedPatternList.push_back(patternStr);
						std::string nonterminal(1, usableNonterminal);
						replacedByList.push_back(nonterminal);
						// replace termial by nontermial in pattern
						newList.push_back(nonterminal + "," + patternStr);
						currPattern.replace(0, 1, nonterminal);
					}
				}
				if (isTerminal(currPattern[1])) {
					if (replacingPatternExist(currPattern[1], replacedPatternList, replacedByList)) {
						std::string by = getByPattern(currPattern[1], replacedPatternList, replacedByList);
						currPattern.replace(1, 1, by);
					}
					else {
						char usableNonterminal = validChar.front();
						validChar.pop_front();
						usedChar.push_back(usableNonterminal);
						std::string patternStr(1, currPattern[1]);
						replacedPatternList.push_back(patternStr);
						std::string nonterminal(1, usableNonterminal);
						replacedByList.push_back(nonterminal);
						// replace termial by nontermial in pattern
						newList.push_back(nonterminal + "," + patternStr);
						currPattern.replace(1, 1, nonterminal);
					}
				}
			}
			newRow += "," + currPattern;
		}
		newList.push_front(newRow);
	}
	CfgRulesInChomsky = newList;
}

bool CFG::replacingPatternExist(char target, std::list<std::string> replacedList, std::list<std::string> byList) {
	while (!replacedList.empty() && !byList.empty()) {
		std::string temp(1, target);
		std::string replaced = replacedList.front();
		std::string by = byList.front();

		replacedList.pop_front();
		byList.pop_front();
		if (temp == replaced) {
			return true;
		}
	}
	return false;
}

std::string CFG::getByPattern(char target, std::list<std::string> replacedList, std::list<std::string> byList) {
	while (!replacedList.empty() && !byList.empty()) {
		std::string temp(1, target);
		std::string replaced = replacedList.front();
		std::string by = byList.front();

		replacedList.pop_front();
		byList.pop_front();
		if (temp == replaced) {
			return by;
		}
	}
	return "";
}

bool CFG::isTerminal(char target) {
	if ((int)target >= 97 && (int)target <= 122) return true;
	else if ((int)target >= 48 && (int)target <= 57) return true;
	else return false;
}

// convert strings into all lower case, for input ending check
std::string CFG::tolower(std::string str) {
	std::string newstr = str;
	for (int i = 0; i < str.length(); i++) {
		if ((int)newstr[i] <= 90 && (int)newstr[i]>=65) {
			char tempchar = (char)((int)newstr[i] + 32);
			std::string tempstr(1, tempchar);
			newstr.replace(i, 1, tempstr);
		}
	}
	return newstr;
}

// replace -> and | to , for further operations
std::string CFG::delimeterReplace(std::string str) {
	std::string newstr = str;
	size_t pos = newstr.find("->");
	while (pos != std::string::npos) {
		newstr.replace(pos, 2, ",");
		pos = newstr.find("->", pos + 1);
	}
	pos = newstr.find("|");
	while (pos != std::string::npos) {
		newstr.replace(pos, 1, ",");
		pos = newstr.find("|", pos + 1);
	}
	return newstr;
}

// check if goal is in checklist
bool CFG::notInList(std::list<char> checkList, char goal) {
	std::list<char> tempList = checkList;
	while (!tempList.empty()) {
		char curr = tempList.front();
		tempList.pop_front();
		if (curr == goal) {
			return false;
		}
	}
	return true;
}

// base on used char list, provide a list that can be used for new nonterminal
void CFG::setValidChar() {
	validChar.clear();
	for (int i = 65; i <= 90; i++) {
		if (notInList(usedChar, (char)i)) {
			validChar.push_back((char)i);
		}
	}
	return;
}

// get nonterminal characters has been used in cfgRulesInChomsky
void CFG::setUsedChar() {
	std::list<std::string> currCFG = CfgRulesInChomsky;
	std::list<std::string> charList;
	while (!currCFG.empty()) {
		std::string currLine = currCFG.front();
		currCFG.pop_front();
		for (int i = 0; i < currLine.length(); i++) {
			if ((int)currLine[i] >= 65 && (int)currLine[i] <= 90 && notInList(usedChar, currLine[i])) {
				usedChar.push_back(currLine[i]);
			}
		}
	}
	return;
}

// parse a string into several string pattern [lhs nonterminal, rhs rule1, rhs rule2, ...]
std::list<std::string> CFG::parse(std::string str) {
	std::list<std::string> patternList;
	std::size_t current, previous = 0;
	current = str.find(',');
	while (current != std::string::npos) {
		patternList.push_back(str.substr(previous, current - previous));
		str.erase(previous, current+1);
		current = str.find(',');
	}
	patternList.push_back(str);
	return patternList;
}

// provide an original string, if it contains the nontermial contains empty string, then get the possible substitutions
std::string CFG::removeEmptyString(std::string str,char nonterminal) {
	std::list<std::string> outList;
	std::list<std::string> parsedList = parse(str);
	outList.push_back(parsedList.front());
	parsedList.pop_front(); // remove the left hand side nonterminal

	while (!parsedList.empty()) {
		std::string currPiece = parsedList.front();
		std::string x(1, nonterminal);
		//if (currPiece == x && currPiece != outList.front()) {
			//outList.push_back("_");
		//}
		if (currPiece != "_") {
			outList.push_back(currPiece);
		}
		parsedList.pop_front();
		std::size_t find = currPiece.find_first_of(nonterminal);
		if (find != std::string::npos && currPiece.length() == 1) {
			outList.push_back("_");
		}
		while (find != std::string::npos) {
			currPiece.erase(find, 1);
			if (currPiece != outList.front()) {
				outList.push_back(currPiece);
			}
			find = currPiece.find_first_of(nonterminal, find + 1);
		}
	}

	// remodify output strings from a string list
	std::string output = "";
	output.append(outList.front());
	outList.pop_front();
	while (!outList.empty()) {
		if (outList.front() != "") {
			output.append("," + outList.front());
		}
		outList.pop_front();
	}

	return output;
}