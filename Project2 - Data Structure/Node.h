// Fernando Rodrigues Cardoso
// Nov. 28, 2019
//Node header

#pragma once

class Node {
public:
	Node* left_;
	Node* right_;
	int data_;
	int condition_;
	Node() : data_(0), condition_(0), left_(nullptr), right_(nullptr) {}
	Node(int val) : data_(val), condition_(0), left_(nullptr), right_(nullptr) {}
	Node(int val, int condition) : data_(val), condition_(condition), left_(nullptr), right_(nullptr) {}
};
#pragma once
