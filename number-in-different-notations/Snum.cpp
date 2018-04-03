#include "Snum.h"

string Snum::nums = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string Snum::convert(string num, int from, int to) {
	assert(to < 37 && to > 1);

	if (from != 10) to_dec(num, from);

	string  res;
	
	for (int n = atoi(num.c_str()); n; n /= to) {
		res.push_back(nums[n % to]);
	}

	reverse(res.begin(), res.end());

	return res;
}

void Snum::to_dec(string &str, int from) {
	int s = str.length(), d, p;

	for (d = 0, p = 0; s > 0; p++, s--) {
		d += nums.find(str[s - 1]) * pow(from, p);
	}

	str = std::to_string(d);
}