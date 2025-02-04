//  Author: li992
//	Date: 2019/10/20
//	Program purpose: graph search program including Depth First Search(dfs) and Breadth First Search(bfs)
//						and also can check a string if it contains a sequence of comment
//

#include <iostream>
#include "graphSearch.h"	// this header is for cs320
#include "ValComment.h"		// this header is for cs350
#include "Chomsky.h"

//void sampleTestCase();
void testSampleOne();

// int main() { return 0; }

void testSampleOne() {
	CFG* ptr = new CFG();
	delete ptr;
}

void CS350Test() {
	std::cout << "CS320 Assignment 2\n student: Qiaoyi Li\n SID:200373380\n\n";
	std::cout << "Please enter the a string for testing\n Enter: ";
	std::string input_str;
	getline(std::cin, input_str);

	if (ifContainComment(input_str)) {
		std::cout << "Result return true\n";
	}
	else {
		std::cout << "Result return false\n";
	}
	return;
}


/*
// Author: li992
// This setting are all premade in order to reduce your input time
// This funtion contains three parts, 1. selft-declare 2. adjacent-declare 3. function call
// self-declare is to define the nodes
// adjacent-declare is to define the adjacent nodes for each nodes
// function-call is to call dfs or bfs
void sampleTestCase() {
	//self-declare
	node A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, R;
	A.set_self('A');
	B.set_self('B');
	C.set_self('C');
	D.set_self('D');
	E.set_self('E');
	F.set_self('F');
	G.set_self('G');
	H.set_self('H');
	I.set_self('I');
	J.set_self('J');
	K.set_self('K');
	L.set_self('L');
	M.set_self('M');
	N.set_self('N');
	O.set_self('O');
	P.set_self('P');
	R.set_self('R');

	//adjacent-declare
	list<node> A_adj, B_adj, C_adj, D_adj, E_adj, F_adj, G_adj, H_adj, I_adj;
	list<node> emptyList = {};
	J.set_adjacent(emptyList);
	K.set_adjacent(emptyList);
	L.set_adjacent(emptyList);
	M.set_adjacent(emptyList);
	N.set_adjacent(emptyList);
	O.set_adjacent(emptyList);
	P.set_adjacent(emptyList);
	R.set_adjacent(emptyList);

	I_adj.clear();
	I_adj.push_back(P);
	I_adj.push_back(R);
	I.set_adjacent(I_adj);

	H_adj.clear();
	H_adj.push_back(O);
	H_adj.push_back(P);
	H.set_adjacent(H_adj);

	G_adj.clear();
	G_adj.push_back(M);
	G_adj.push_back(N);
	G_adj.push_back(H);
	G.set_adjacent(G_adj);

	F_adj.clear();
	F_adj.push_back(L);
	F.set_adjacent(F_adj);

	E_adj.clear();
	E_adj.push_back(J);
	E_adj.push_back(K);
	E_adj.push_back(L);
	E.set_adjacent(E_adj);

	D_adj.clear();
	D_adj.push_back(H);
	D_adj.push_back(I);
	D.set_adjacent(D_adj);

	C_adj.clear();
	C_adj.push_back(G);
	C.set_adjacent(C_adj);

	B_adj.clear();
	B_adj.push_back(E);
	B_adj.push_back(F);
	B_adj.push_back(G);
	B.set_adjacent(B_adj);

	A_adj.clear();
	A_adj.push_back(B);
	A_adj.push_back(C);
	A_adj.push_back(D);
	A.set_adjacent(A_adj);

	list<node> nodes = {};
	nodes.clear();
	nodes.push_back(A);
	nodes.push_back(B);
	nodes.push_back(C);
	nodes.push_back(D);
	nodes.push_back(E);
	nodes.push_back(F);
	nodes.push_back(G);
	nodes.push_back(H);
	nodes.push_back(I);
	nodes.push_back(J);
	nodes.push_back(K);
	nodes.push_back(L);
	nodes.push_back(M);
	nodes.push_back(N);
	nodes.push_back(O);
	nodes.push_back(P);
	nodes.push_back(R);

	//Function-call
	//question 3.1
	std::cout << "3.1 Node N Search:\n";
	graph* NDFSGraph = new graph();
	NDFSGraph->set_vertices(nodes);
	std::cout << "	Depth First Search:\n";
	NDFSGraph->DFS('N');

	std::cout << std::endl;

	graph* NBFSGraph = new graph();
	NBFSGraph->set_vertices(nodes);
	std::cout << "	Breadth First Search:\n";
	NBFSGraph->BFS('N');

	std::cout << std::endl << std::endl;

	//question 3.2
	std::cout << "3.2 Node P Search:\n";
	graph* PDFSGraph = new graph();
	PDFSGraph->set_vertices(nodes);
	std::cout << "	DepthFirst Search:\n";
	PDFSGraph->DFS('P');
	std::cout << std::endl;
	graph* PBFSGraph = new graph();
	PBFSGraph->set_vertices(nodes);
	std::cout << "	Breadth First Search:\n";
	PBFSGraph->BFS('P');

	return;
}
*/