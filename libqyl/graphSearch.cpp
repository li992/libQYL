#include "graphSearch.h"

// logic of DFS and BFS:
//		In this program I used std::list<T>, which is pretty much like a linked list
//		In list<T>, it contains function like, list.front() & list.back() to get first and last element
//		It also has function like, list.pop_front()/back() and list.push_front()/back() so it can be either a stack or a queue or it can be both at the same time
//		the main difference between dfs an bfs is when I'm pushing a new element in, in dfs I will push it to the front and in bfs I will push it to the back. I'm reading the list from front all the time.
//		Line 35 and Line 71 are the only difference
void graph::DFS(char goal) {
	list<node> closed = {};
	list<node> open;
	list<node> graph_nodes = get_vertices();
	node start_state = graph_nodes.front();

	graph_nodes.pop_front();
	open.push_front(start_state);

	while (!open.empty()) {
		node current_state = open.front();
		open.pop_front();
		closed.push_front(current_state);
		if (current_state.get_self() == goal) {
			printPath(current_state,closed);
			break;
		}
		else {
			list<node> children = current_state.get_adjacent();
			while (!children.empty()) {
				node target = children.front();
				children.pop_front();
				bool findInClosed = find(closed, target);
				bool findInOpen = find(open, target);
				if (!findInClosed && !findInOpen){
					target.set_parent(current_state);
					target.set_parentChar(current_state.get_self());
					open.push_front(target);
				}
			}
		}
	}
	return;
}

void graph::BFS(char goal) {
	list<node> closed = {};
	list<node> open;
	list<node> graph_nodes = get_vertices();
	node start_state = graph_nodes.front();

	graph_nodes.pop_front();
	open.push_front(start_state);

	while (!open.empty()) {
		node current_state = open.front();
		open.pop_front();
		closed.push_front(current_state);
		if (current_state.get_self() == goal) {
			printPath(current_state, closed);
			break;
		}
		else {
			list<node> children = current_state.get_adjacent();
			while (!children.empty()) {
				node target = children.front();
				children.pop_front();
				bool findInClosed = find(closed, target);
				bool findInOpen = find(open, target);
				if (!findInClosed && !findInOpen) {
					target.set_parent(current_state);
					target.set_parentChar(current_state.get_self());
					open.push_back(target);
				}
			}
		}
	}
	return;
}


// internal functions that will be called in DFS and BFS
bool graph::find(list<node>lst, node target) {
	while (!lst.empty()) {
		node listfront = lst.front();
		lst.pop_front();
		if (listfront.get_self() == target.get_self()) {
			return true;
		}
	}
	return false;
}

void graph::printPath(node curr,list<node> closed) {
	list<char> path;
	while (curr.get_parent()!=NULL) {
		path.push_front(curr.get_self());
		curr = getNode(curr.get_parent(),closed);
	}
	if (curr.get_self() == 'A') {
		path.push_front('A');
	}
	if (!closed.empty()) {
		cout << "	Searching Root: ";
		while (!closed.empty()) {
			cout << closed.back().get_self();
			closed.pop_back();
		}
		cout << endl;
	}
	if (!path.empty()) {
		cout << "	Path Found: ";
	}
	while (!path.empty()) {
		cout << path.front();
		path.pop_front();
	}
	cout << endl;
	return;
}

node graph::getNode(char target,list<node> closed) {
	node empty_node = {};
	list<node> nodelist = closed;
	while (!nodelist.empty()) {
		node temp = nodelist.front();
		nodelist.pop_front();
		if (temp.get_self() == target) {
			return temp;
		}
	}
	return empty_node;
}