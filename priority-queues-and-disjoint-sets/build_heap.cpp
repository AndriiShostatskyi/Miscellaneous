#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HeapBuilder {
	vector<int> data_;
	vector< pair<int, int> > swaps_;

	void WriteResponse() const {
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i)
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
	}

	void ReadData() {
		int n;
		cin >> n;
		data_.resize(++n);
		for (int i = 1; i < n; ++i)
			cin >> data_[i];
	}

	void SiftDown(int i, int sz) {
		int maxIndex = i, l, r;

		l = 2 * i;
		if (l <= sz && data_[l] < data_[maxIndex])
			maxIndex = l;

		r = 2 * i + 1;
		if (r <= sz && data_[r] < data_[maxIndex])
			maxIndex = r;

		if (i != maxIndex) {
			swap(data_[i], data_[maxIndex]);
			swaps_.push_back(make_pair(i - 1, maxIndex - 1));
			SiftDown(maxIndex, sz);
		}
	
	}

	void GenerateSwaps() {
		swaps_.clear();
		for (int sz = data_.size(), i = --sz / 2; i; i--)
			SiftDown(i, sz);
	}

public:
	void Solve() {
		ReadData();
		GenerateSwaps();
		WriteResponse();
	}
};


int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
