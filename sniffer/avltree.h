#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// AVL tree node
struct Node
{
    unsigned int ip; // string ip address
	  unsigned int cnt; // number of packets received
	  unsigned int height;
    struct Node *left;
    struct Node *right;
};

// Get height of the tree
int height(struct Node*);

// Get maximum of two integers
int max(int a, int b);

// Allocates a new node with the given key (ip) and NULL left and right pointers.
struct Node* newNode(unsigned int);

// Iterative function to find the node that has the given key (ip) or is the closest to that
struct Node *_find(struct Node *, unsigned int);

// Recursive function to insert key (ip) in subtree rooted with node and returns new root of subtree.
struct Node* insert(struct Node*, unsigned int);

// Right rotate subtree rooted with y
struct Node *rightRotate(struct Node*);

// Left rotate subtree rooted with x
struct Node *leftRotate(struct Node*);

// Get Balance factor of node N
int getBalance(struct Node*);

// Preorder traversal of the tree.
void preOrder(struct Node*);
