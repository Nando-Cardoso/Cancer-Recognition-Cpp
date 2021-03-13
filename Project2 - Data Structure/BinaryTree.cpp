// Fernando Rodrigues Cardoso
// Nov. 28, 2019
// Defining the functions for BinaryTree class

#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#include "BinaryTree.h"

using namespace std;

//Recursive search entire binary tree to determine if patient is benign or malign
int BinaryTree::recursiveSearch(Node*& leaf, int i, int condition)
{
	if (leaf->data_ <= condition)
	{
		if (leaf->left_ == nullptr) {
			return leaf->data_;
		}
		i++;
		recursiveSearch(leaf->left_, i, leaf->left_->condition_);
	}

	else
	{
		if (leaf->right_ == nullptr) {
			return leaf->data_;
		}
		i++;
		recursiveSearch(leaf->right_, i, leaf->right_->condition_);
	}
}

//insert into binary tree
void BinaryTree::insert(int value, int condition, Node*& leaf)
{
	if (leaf == nullptr)
	{
		leaf = new Node(value, condition);
		return;
	}
	if (value <= leaf->data_)
	{
		insert(value, condition, leaf->left_);
	}
	else if (value > leaf->data_)
	{
		insert(value, condition, leaf->right_);
	}
}