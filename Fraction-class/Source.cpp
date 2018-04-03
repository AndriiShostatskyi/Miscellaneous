#include "Fraction.h"
#include <iostream>
using namespace std;

/*
   C++ OOP learning task: create fraction class with operators overloading, including new, 
   creation of an object with 0 as denominator should be avoided
*/

void main() {
	Fraction *f1 = new Fraction(5, 5), f2(5, 20);
	cout << f1->getNum() << " / " << f1->getDen() << endl;
	f2 += *f1;
	cout << f2.getNum() << " / " << f2.getDen() << endl;
	delete f1;
	system("pause");
}