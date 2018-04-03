#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
	int size, parent, rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
		size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size) : size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	// Find parent and compress path
	int getParent(int table) {
		if (table != sets[table].parent)
			sets[table].parent = getParent(sets[table].parent);
		return sets[table].parent;
	}


	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);

		// Check if the tables requested to be mereged are in the same disjoint set
		if (realDestination != realSource) {

			/* If the rank of the second table is smaller than the rank of the first table, ignore 
			   the requested order and join the node corresponding to the second table to the node 
			   corresponding to the first table instead. */
			if (sets[realDestination].size < sets[realSource].size) {
				int tmp = realDestination;
				realDestination = realSource, realSource = tmp;
			}
				
			// Merge two components
			if (sets[realDestination].rank > sets[realSource].rank) {
				sets[realSource].parent = realDestination;
				sets[realDestination].size += sets[realSource].size;
				sets[realSource].size = 0;

				// Update max_table_size with the new maximum table size
				if (sets[realDestination].size > max_table_size) 
					max_table_size = sets[realDestination].size;
			}
			else {
				sets[realDestination].parent = realSource;
				sets[realSource].size += sets[realDestination].size;
				sets[realDestination].size = 0;
			
			    // Use union by rank heuristic
				if (sets[realDestination].rank == sets[realSource].rank)
					sets[realSource].rank++;

				// Update max_table_size with the new maximum table size
				if (sets[realSource].size > max_table_size)
					max_table_size = sets[realSource].size;
			}
		}
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;
		
		tables.merge(destination, source);
	        cout << tables.max_table_size << endl;
	}

	return 0;
}
