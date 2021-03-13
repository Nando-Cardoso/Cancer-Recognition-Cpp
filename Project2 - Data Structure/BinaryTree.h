// Fernando Rodrigues Cardoso
// Nov. 28, 2019
//BinaryTree class header

#pragma once
#include "Node.h"
#include <vector>

class BinaryTree
{
public:

	Node* root_;

	BinaryTree() : root_(nullptr) {}
	BinaryTree(Node* root_) : root_(root_) {}
	~BinaryTree() { delete root_; }

	void inorder(Node* root);
	int recursiveSearch(Node*& leaf, int i, int condition);
	void insert(int value, int condition, Node*& leaf);;
};

#pragma once
