#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
struct Node {
	T data;
	Node *next;
	Node *prev;
};


template <class T>
class List {
private:   
	Node<T> *head;
	Node<T> *tail;

public:
	List(): head(NULL), tail(NULL) {}
	~List();
	void show();
	void push_front(T);
	void push_back(T);
	void insert_after(int i, T data);
	T pop_back();
	T pop_front();
};



