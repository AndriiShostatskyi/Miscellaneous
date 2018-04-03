#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

class Snum {
	static string nums;
	static void to_dec(string &str, int from);
    public:
		static string convert(string num, int from, int to);
};
