#include <iostream>

class Fraction { 
	int _num;
	int _den;

public:
	Fraction() : _num(1), _den(1) {}
	Fraction(int n) : _num(n), _den(1) {}
	Fraction(int, int);
	Fraction(const Fraction &number);

	int getNum() const { return _num; }
	int getDen() const { return _den; }

	void setNum(int);
	void setDen(int);

	void add(Fraction b);
	void subtruct(Fraction b);
	void multiply(Fraction b);
	void devide(Fraction b);
 
	Fraction& operator = (Fraction f) { _num = f.getNum(), _den = f.getDen(); return *this; };
	Fraction& operator = (Fraction *f) { _num = f->getNum(), _den = f->getDen(); return *this; };

	Fraction& operator += (Fraction f) { this->add(f); return *this; };
	Fraction& operator -= (Fraction f) { this->subtruct(f); return *this; };
	Fraction& operator *= (Fraction f) { this->multiply(f); return *this; };
	Fraction& operator /= (Fraction f) { this->devide(f); return *this; };
	operator double() { return _num / _den; };
	operator int() { return _num / _den; };

	static void com_denom(Fraction &a, Fraction &b);
	void* operator new[](size_t sz) { return malloc(sz); }
	double decimal() { return (double)_num / (double)_den; }
}; 