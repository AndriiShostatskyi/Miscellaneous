#include <iostream>
#include <algorithm>  
#include "BT.h"
using namespace std;

node* BT::find(int k) // if didn't find, then it returns the closest to the searched one
{
	node* r = root;
	while (true) {
		if (r->key == k) {
			return r;
		}
		else if (r->key > k) {
			if (!r->left) return r;  
			return r = r->left;
		}
		else if (r->key < k) {
			if (!r->right) return r;  
			r = r->right;
		}
	}
}

node* BT::newNode(int k)
{
	node *n = new node[1];
	n->key = k;
	n->left = n->right = NULL;
	return n;
}

void BT::insert(int k)
{
	if (!root) { 
		root = newNode(k);
		root->parent = NULL;
		return;
	}

	node *current = root, *parent = root; 
	while (current) { 
		parent = current;
		if (k < current->key)
			current = current->left;
		else if (k > current->key)
			current = current->right;
	}
	if (parent->key < k)
		parent->right = newNode(k), parent->right->parent = parent;
	else parent->left = newNode(k), parent->left->parent = parent;
}

void BT::level_order()
{
	if (!root) return;
	queue<node*> q;
	q.push(root);
	for (node *n; !q.empty();) {
		n = q.front();
		cout << n->key << ' ';
		q.pop();
		if (n->left)
			q.push(n->left);
		if (n->right)
			q.push(n->right);
	}
	cout << endl;
}

void BT::in_order()
{
	node* r = root,* tmp;
	for (stack<node*> st; true;) {
		if (r) {
			st.push(r);
			r = r->left;
		} else {
			if (st.empty()) break;
			tmp = st.top();
			st.pop();
			r = tmp->right;
			cout << tmp->key << " ";
		}
	} cout << endl;
}

void BT::pre_order()
{
	node* r = root, *tmp;
	for (stack<node*> st; true;) {
		if (r) {
			st.push(r);
			cout << r->key << " ";
			r = r->left;
		}
		else {
			if (st.empty()) break;
			tmp = st.top();
			st.pop();
			r = tmp->right;
		}
	} cout << endl;
}

void BT::post_order()
{
	node* r = root, *tmp;
	for (stack<node*> st; r || !st.empty();) {
		if (r) {
			st.push(r);
			r = r->left;
		}
		else {
			tmp = st.top()->right;
			if (!tmp) {
				tmp = st.top();
				cout << tmp->key << ' ';
				st.pop();
				while (!st.empty() && tmp == st.top()->right) {
					tmp = st.top();
					cout << tmp->key << ' ';
					st.pop();
				}
			}
			else r = tmp;
		}
	} cout << endl;
}