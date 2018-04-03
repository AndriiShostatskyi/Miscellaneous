#include <iostream>
using namespace std;

/*
   C++ OOP learning task: make an inner class; 
   from that inner class access variables of its outer class.
*/

class A {
public:
	class B {
		int b;
	    public:
		     B(int v) : b(v) {}
			 void show() { cout << "inner = " << b << ", outer = " << *((int*)&b - 1) << endl; } // accessing outer
	};
	A(int v): a(v), b(v + 10) {}
	int a;
	B b;
};
void main() {
	A a(10);
	a.b.show();

	system("pause");
}
