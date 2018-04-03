#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib> 
#include <memory>

using namespace std;

struct Data {
	string pattern, text;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

class RabinKarp
{
	static bool AreEqual(const char *T, size_t psize, const char *P)
	{
		while(P)
			if (*T++ != *P++)
				return false;
		return true;
	}

	static long long PolyHash(const char* S, int psize, const size_t &multiplier, const size_t& prime) 
	{
		long long hash = 0;
		for (int i = psize - 1; i >= 0; --i)
			hash = (hash * multiplier + *S--) % prime;
		return ((hash % prime) + prime) % prime;
	}

	static unique_ptr<long long[]> PrecomputeHashes(const string &t, const string&p, const size_t &x, const size_t& prime)
	{
		unique_ptr<long long[]> H = unique_ptr<long long[]> (new long long[t.size() - p.size() + 1]);
		H[t.size() - p.size()] = PolyHash(&t[t.size() - 1], p.size(), x, prime);
		long long y = 1, tmp;
		for (int i = 0; i < p.size(); ++i)
			y = (y * x) % prime;

		for (int i = t.size() - p.size() - 1; i > -1; --i) {
			tmp = (x * H[i + 1] + t[i] - y*t[i + p.size()]);
			H[i] = ((tmp % prime) + prime) % prime;
		}
		return H;
	}

public:
	static list <int> FindPattern(const string &T, const string &P) 
	{
		list <int> result;
		time_t aTime;            
		srand(static_cast<unsigned>(time(&aTime)));
		const long long prime = 1000000007, multiplier = rand() % prime - 1;
	    long long pHash = PolyHash(P.c_str() + P.size() - 1, P.size(), multiplier, prime);
		unique_ptr<long long[]>  H = PrecomputeHashes(T, P, multiplier, prime);

		for (int i = 0, s = T.size() - P.size(); i <= s; ++i) {
			if (pHash != H[i])
				continue;
			else {
				if (AreEqual(&T[i], P.size(), &P[0]))
					result.push_back(i);
			}
		}
		return result;
	}
};

void print_occurrences() {
	Data dt = read_input();
	list <int> result = RabinKarp::FindPattern(dt.text, dt.pattern);
	for (auto x : result)
		cout << x << " ";
	std::cout << "\n";
}

int main() {
	
	std::ios_base::sync_with_stdio(false);
	print_occurrences();

	return 0;
}
