#include "List.h"

template <class T>
List<T>::~List()
{
	for (; head; delete (*head).prev, head = (*head).next);
}

template <class T>
void List<T>::push_front(T val)
{
	Node<T> *n = new Node<T>;
	n->data = val;
	n->next = head;
	n->prev = NULL;
	if (head) head->prev = n;
	else tail = n;
	head = n;
}

template <class T>
void List<T>::push_back(T val)
{
	Node<T> *n = new Node<T>;
	n->data = val;
	n->prev = tail;
	n->next = NULL;
	if (head) tail->next = n;
	else head = n;
	tail = n;
}

template <class T>
T List<T>::pop_back() {
	T tmp = tail->data;
	Node<T> *p = tail;
	tail = tail->prev;
	tail->next = NULL;
	delete p;
	return tmp;
}

template <class T>
T List<T>::pop_front() {
	T tmp = head->data;
	Node<T> *p = head;
	head = head->next;
	head->prev = NULL;
	delete p;
	return tmp;
}

template <class T>
void List<T>::insert_after(int i, T data) {
	if(!i) this->push_front(data);
	
	Node<T> *p = head;
	for (; i--; p = p->next)
		assert(p);
	assert(p);
	
	if (p == tail) 
		this->push_back(data);
	else {
		Node<T> *n = new Node<T>;
		n->data = data;
		n->next = p->next;
		n->prev = p;
		p->next->prev = n;
		p->next = n;
	}
}

template <class T>
void List<T>::show()
{
	Node<T> *p1 = head, *p2 = tail;

	for (; head; head = (*head).next)
		std::cout << (*head).data << ' ';

	std::cout << std::endl;

	for (; tail; tail = (*tail).prev)
		std::cout << (*tail).data << ' ';

	std::cout << std::endl;

	head = p1, tail = p2;
}
