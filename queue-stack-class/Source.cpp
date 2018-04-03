#include "QS.h"

/*
   Ñ++ OOP learning task: make a Queue & Stack class. 
   This class shall create a stack or queue object depending on a parameter passed into its
   constructor (true or false) (for that purpose, a pointer to function is used).
   Stack is by default if nothing passed into the constructor. The class should also
   have the method that finds and returns the middle element (its val) in a stack/queue.
   Only ints are acceptable as values, and templates are not used here. The list is single-linked.
*/

void main() {
	QS lst(true);
	lst.push(24);
	lst.push(11);
	lst.push(17);
	lst.push(29);
	lst.push(21);
	cout << lst.find_mdl() << endl;
	lst.show();
	cout << lst.pop() << endl;
	lst.show();

	system("pause");
}