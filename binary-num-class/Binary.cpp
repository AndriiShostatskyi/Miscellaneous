#include "Binary.h"

Binary& Binary::operator++() {
	int i = _num.length();

	// Go until 0 or end of the string
	while (i && _num[i - 1] - 48 ) _num[i-- - 1] = '0';

	// Check if the string needs to be longer to keep the num
	if (i == 0) _num[i] = '0', _num.insert(0, "1");
	else _num[i-1] = '1';
	
	return *this;
}

void Binary::inc(string &str, int i) {
	// Go until 0 or end of the string
	for (; i && str[i] - 48; i--) str[i] = '0';

	// Check if the string needs to be longer to keep the num
	if (i == 0) str[i] = '0', str.insert(0, "1");
	else str[i] = '1';
}

Binary& Binary::operator++(int) {
	return ++*this;
}

Binary& Binary::operator+=(const Binary &n) {
	string str1, str2, str3;
	int s1, s2, dif, i;

	// First, check strings' length and prep vars for addition
	if (_num.length() > n.getN().length()) {
		str1 = _num,     s1 = _num.length();
		str2 = n.getN(), s2 = n.getN().length();
	}
	else {
		str1 = n.getN(), s1 = n.getN().length(), str2 = _num, s2 = _num.length();
	}

	// Find the difference in length
	dif = s1 - s2;

	// Make strings' length the same by prepending the shorter string with zeros
	for (i = dif; i--; str3.push_back('0'));

	// Finally, prepend the shorter string and do the addition in an efficient way
	for (str3 += str2, i = s2 + dif; i; i--)
		if (str3[i - 1] == '1') inc(str1, i - 1);

	this->_num = str1;

	return *this;
}

Binary Binary::operator+(const Binary &n) {
	Binary tmp(_num);
    return tmp += n;
}