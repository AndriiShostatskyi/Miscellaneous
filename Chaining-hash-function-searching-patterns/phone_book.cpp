#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

/* Solved simply by means of unordered map as my Visual Studio 2015 did not allow 
   to use the direct addressing scheme with memory allocation 10^5 */

using namespace std;

struct Query {
	string type, name;
	int number;
};

vector<Query> read_queries() {
	int n;
	cin >> n;
	vector<Query> queries(n);
	for (int i = 0; i < n; ++i) {
		cin >> queries[i].type;
		if (queries[i].type == "add")
			cin >> queries[i].number >> queries[i].name;
		else
			cin >> queries[i].number;
	}
	return queries;
}

void write_responses(const vector<string>& result) {
	for (size_t i = 0; i < result.size(); ++i)
		cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries) {
	vector<string> result;
	unordered_map<int, string> contacts;
	for (auto &query : queries)
		if (query.type == "add") {
			contacts[query.number] = query.name;
		}
		else if (query.type == "del") {
			if (contacts.find(query.number) != contacts.end())
				contacts.erase(contacts.find(query.number));
		}
		else {
			result.push_back(contacts.find(query.number) == contacts.end() ? "not found" : contacts[query.number]);
		}
		return result;
}

int main() {
	write_responses(process_queries(read_queries()));
	
	return 0;
}
