#include "QS.h"

void QS::push_fornt(int v) {
	st *n = new st;
	n->val = v;
	n->next = root ? root : NULL;
	root = n;
}
void QS::push_back(int v) {
	st* p = root;
	if (p) for (; p->next; p = p->next);
	st *n = new st;
	n->val = v; n->next = NULL;
	if (p) p->next = n; else root = n;
}

void QS::show() const {
	st* p = root;
	for (; p; p = p->next) cout << p->val << ' '; cout << endl;
}

int QS::find_mdl() const {
	st* p = root, *pn = root;
	if (!p) return NULL;
	for (; pn->next; p = p->next) {
		if (!pn->next->next) return p->val;
		else pn = pn->next->next;
	}
	return p->val;
}

int QS::pop() {
	int tmp = root->val;
	st* p = root;
	root = root->next;
	delete p;
	return tmp;
}