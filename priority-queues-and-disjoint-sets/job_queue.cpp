#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Worker {
	int _index;
	long long _time;
	Worker(int i, long long t) : _index(i), _time(t) {}
	bool operator < (const Worker &b) const { 
		if (_time == b._time) 
			return (_index > b._index);
		return (_time < b._time); 
	}
};

class JobQueue {
private:
	int num_workers_;
	vector<int> jobs_;
	vector<int> assigned_workers_;
	vector<long long> start_times_;

	void WriteResponse() const {
		for (int i = 0; i < jobs_.size(); ++i)
			cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
	}

	void ReadData() {
		int m;
		cin >> num_workers_ >> m;
		jobs_.resize(m);
		for (int i = 0; i < m; ++i)
			cin >> jobs_[i];
	}

	void AssignJobs() {
		assigned_workers_.resize(jobs_.size());
		start_times_.resize(jobs_.size());

		priority_queue<Worker> pq;
		int ind, i = 0, sz = jobs_.size(), *aw = &assigned_workers_[0], *jb = &jobs_[0];
		long long tim, *st = &start_times_[0];

		for (; i < num_workers_ && i < sz; ++i)
			pq.push(Worker(i, -((long long)*jb++))), *aw++ = i, *st++ = 0;

		for (; i++ < sz; pq.pop(), pq.push(Worker(ind, -((long long)*jb++ + tim)))){
			ind = pq.top()._index;
			tim = -(pq.top()._time);
			*aw++ = ind, *st++ = tim;
		}
	}

public:
	void Solve() {
		ReadData();
		AssignJobs();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	JobQueue job_queue;
	job_queue.Solve();

	return 0;
}
