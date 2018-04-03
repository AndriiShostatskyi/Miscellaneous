/*
   C++ OOP learning task: overload operator '[][]'.
   Here, I use inner struct as intermidiate for the second [].

*/

#include<iostream>
using namespace std;

class A {
	int *arr;
	int r;
	struct u {
		int *p;
		int & operator [](int j) { return *(p + j); }
	};
public:
	A(int *p, int row) : arr(p), r(row) {}
	u operator [](int i) {
		u a; a.p = this->arr + i * r;
		return a;
	}
};

void main() {
	int ar[2][2] = { { 2,4 },{ 6,7 } };
	A p(*ar, 2);
	p[1][1] = 124;
	int a = p[1][1];
	cout << a;
	system("pause");
}
