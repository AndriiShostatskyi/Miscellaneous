#include "Binary.h"

/*
  C++ OOP learning task: make a class object of which represents a binary number;
  the required methods are ++ and +=. In such a class, the number is an instance of std::string;
  it should be enlarged if addition so requires while addition should not lead to redundant
  zeros at the beginning of the number. The required methods here implement I in an efficient 
  way (i.e. ordinary addition with carrying forward ones and checking like 1 & 1, 1 || 1, 0 & 0 
  requires many ifs in each iteration, which is, in my opinion, not effective). 

*/

void main()
{
	Binary num1("100111"), num2("01101110111"); // 39 + 887
	num1.show();
	num1 += num2;
	num1.show(); // 926 or 01110011110
	cout << endl;
	
	Binary num3("100111"), num4("100111"); // 39 + 39
	num3.show();
	num3 += num4;
	num3.show(); // 1001110 or 78
	cout << endl;

	Binary num5("01101110111"), num6("100111"); // 887 + 39
	num5.show();
	num5 += num6;
	num5.show(); // 926 or 01110011110
	cout << endl;

	Binary num7("100111"); // 39
	num7.show();

	for (int i = 30; i--; num7++);
	num7.show(); // the last is 69 or 1000101

	system("pause");
}


