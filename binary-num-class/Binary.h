#include <iostream>
#include <string>
using namespace std;

class Binary {
	string _num;
    public:
		Binary(string str): _num(str) {}
		Binary& operator++();
		Binary& operator++(int);
		Binary& operator+=(const Binary &n);
		Binary operator+(const Binary &n);
		void show() const { cout << _num << endl; }
		void Binary::inc(string &str, int i);
		string getN() const { return _num; }
};
