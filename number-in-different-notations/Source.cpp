#include "Snum.h"

/*
   C++ OOP learning task: make a class “Number in different notations”, which would 
   allow the user to convert a given number from one notation to other. The class’s notations
   converter method is static, accepts a number in std::string, int from, int to, 
   and then returns the resulting number in std::string.
*/

void main(){
	string num = "123";

	num = Snum::convert(num, 10, 16);
	cout << num << endl;

	num = Snum::convert(num, 16, 2);
	cout << num << endl;

	num = Snum::convert(num, 2, 8);
	cout << num << endl;

	num = Snum::convert(num, 8, 29);
	cout << num << endl;

	num = Snum::convert(num, 29, 31);
	cout << num << endl;

	num = Snum::convert(num, 31, 10);
	cout << num << endl;

	system("pause");
}
