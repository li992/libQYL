#include "ValComment.h"

bool ifContainComment (string str) {
	if (str.length() == 0) {
		return false;
	}

	list<char> char_lst, com_lst;
	for (int i = 0; i < str.length(); i++) {
		char_lst.push_back(str[i]);
	}

	int start_state = 0, end_state = 0;
	bool contain_comment = false;

	while (!char_lst.empty()) {
		char top_char = char_lst.front();
		char_lst.pop_front();

		// this will deal with '/' input
		if (top_char == '/' && start_state == 0) {
			start_state = 1;
		}
		else if (top_char == '/' && start_state == 2 && end_state == 1) {
			end_state = 2;
		}

		// the following code deals with '*' input
		if (top_char == '*' && start_state == 1) {
			start_state = 2;
		}
		else if (top_char == '*' && start_state == 2) {
			end_state = 1;
		}

		// this following code deals with other char inputs
		if (top_char != '*' && top_char != '/') {
			if (start_state == 1) {
				start_state = 0;
			}
			if (end_state == 1) {
				end_state = 0;
			}

			if (start_state == 2 && end_state == 0) {
				com_lst.push_back(top_char);
			}
		}
	}

	if (start_state == 2 && end_state == 2) {
		cout << "Comment string: ";
		while (!com_lst.empty()) {
			cout << com_lst.front();
			com_lst.pop_front();
		}
		cout << endl;
		return true;
	}
	else {
		if (start_state == 2 && end_state != 2) {
			cout << "Error 1: comment string did not close properly!" << endl;
		}
		return false;
	}
}