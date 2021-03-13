// Fernando Rodrigues Cardoso
// Nov. 28, 2019
//NodeGraph header

#pragma once

class NodeGraph {
public:
	int data_;
	int dest_;
	NodeGraph* next_;
	NodeGraph(int des, int dat) : dest_(des), data_(dat), next_(nullptr) {};
	~NodeGraph() { delete next_; }
};