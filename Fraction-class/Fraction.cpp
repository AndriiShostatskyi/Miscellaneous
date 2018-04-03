#include "Fraction.h"
#include <assert.h>

Fraction::Fraction(int num, int den)
{   
	assert(den);
	_num = num;
	_den = den;
}

Fraction::Fraction(const Fraction &number)
{
	assert(number._den);
	_num = number._num;
	_den = number._den;
}

void Fraction::setDen(int val) 
{
	assert(val);
	_den = val;
}

void Fraction::setNum(int val)
{
	_num = val;
}

void Fraction::com_denom(Fraction &a, Fraction &b) 
{
	int tmp1 = a.getDen(), tmp2 = b.getDen(), lcm;
	while (tmp1 != tmp2) {   
		if (tmp1 > tmp2)
			tmp1 -= tmp2;
		else
			tmp2 -= tmp1;
	}
	lcm = a._den * b._den / tmp1;
	a._num *= lcm / a._den;
	a._den *= lcm / a._den;
	b._num *= lcm / b._den;
	b._den *= lcm / b._den;
}

void Fraction::add(Fraction b) 
{   
	if (this->getDen() != b.getDen())
		com_denom(*this, b);
	_num += b._num;
}

void Fraction::subtruct(Fraction b)
{
	if (this->getDen() != b.getDen())
		com_denom(*this, b);
	_num -= b._num;
}

void Fraction::multiply(Fraction b)
{
	_num *= b._num;
	_den *= b._den;
}

void Fraction::devide(Fraction b)
{
	_num *= b._den;
	_den *= b._num;
}