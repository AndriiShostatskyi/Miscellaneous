#pragma once
#include <queue>
#include <stack>
using namespace std;

struct node {
	int key;
	node *parent, *left, *right;
};

// Binary tree class 
class BT {
protected:
	node *root;
public:
	BT(): root(NULL) {}
	node* find(int k); // interative 
	node* getR() const { return root; };
	node* newNode(int k);
	void insert(int k); // interative 
	
	/* 
	   The following are interative traversals of binary tree.
	   The methods are void and their result is std::cout since this class is for learing purpose only 
	*/

	// Breadth-first: 
	void level_order();

	// Depth-first: 
	void in_order();
	void pre_order();
	void post_order();	
};

