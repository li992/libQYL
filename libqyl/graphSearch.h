#include <string.h>
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>
using namespace std;


class node {
private:
	char self;						
	list<node> adjacent_nodes;		
	node* parent_node;				// useless when running, was going to use memory address to allocate nodes
	char parent;					// parent.self()
public:
	node() { self = '0'; adjacent_nodes = {}; parent_node = NULL; parent = NULL; }

	// getters
	list<node> get_adjacent() { return adjacent_nodes; }
	char get_self() { return self;}
	node* get_parentAddress() { return parent_node; }
	char get_parent() { return parent; }

	//setters
	void set_parent(node parent) { parent_node = &parent; }
	void set_self(char a) { self = a; }
	void set_adjacent(list<node> adj) { adjacent_nodes = adj; }
	void set_parentChar(char p) { parent = p; }
};

class graph {
private:
	list<node> vertices;

	// internal functions:
	void printPath(node curr, list<node> closed);	// this will print the path that finds target
	bool find(list<node> lst, node target);			// funtion to find a target node in lst, return true if find, else false
	node getNode(char target, list<node> closed);	// find a target in closed node list, this compares the self property of each node.
public:
	// external functions:
	graph() { vertices = {}; };
	list<node> get_vertices() { return vertices; }
	void set_vertices(list<node> preset) {
		vertices = preset;
	}

	void DFS(char goal);	// Depth First Search
	void BFS(char goal);	// Breadth First Search

};
