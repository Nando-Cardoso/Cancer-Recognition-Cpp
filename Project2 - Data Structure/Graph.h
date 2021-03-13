// Fernando Rodrigues Cardoso
// Nov. 28, 2019
//Graph header

#pragma once
#include <iostream>
#include <vector>
#include "NodeGraph.h"

class Graph {
public:

	std::vector< std::vector<NodeGraph*> > adjMatrix;
	int numVertices_;
	Graph(int vertices);
	~Graph();
	void addEdge(int, int);
	void changeWeight(int, int, int);
	void printAndOutputGraph(int cancerType);


};