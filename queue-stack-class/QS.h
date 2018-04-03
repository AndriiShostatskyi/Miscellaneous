#include <iostream>
using namespace std;

struct st {
	int val;
	st* next;
};

// Queue & Stack class
class QS {
	st *root;
	void push_fornt(int v);
	void push_back(int v);
public:
	QS() : root(NULL), insert(&QS::push_fornt) {}
	QS(bool lifo) : root(NULL), insert(lifo ? &QS::push_fornt : &QS::push_back) {}
	void (QS::*insert)(int v);
	void push(int v) { (*this.*(*this).insert)(v); }
	int pop();
	void show() const;
	bool empty() const { return root ? false : true; }
	int find_mdl() const;
};
