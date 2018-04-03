#include<iostream>
#include "BT.h"
using namespace std;

/*
   C++ OOP and data structures learning task: create binary tree class with insert, find, 
   and traversals methods that are interative and not recursive 
*/

void main()
{
	BT btr;
	btr.insert(10);
	btr.insert(20);
	btr.insert(5);
	btr.insert(15);
	btr.insert(8);
	btr.insert(3);
	btr.insert(17);
	
	cout << "Level-order traversal: ";
	btr.level_order();

	cout << "Inorder traversal: ";
	btr.in_order();

	cout << "Preorder traversal: ";
	btr.pre_order();

	cout << "Postorder traversal: ";
	btr.post_order();

	system("pause");
}