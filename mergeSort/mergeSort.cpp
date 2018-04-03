#include <iostream>
using namespace std;
#define Lm(m) sizeof(m)/sizeof(*m)

void merge(int *a1, int s1, int *a2, int s2) {
	int *pcur = new int[s1 + s2], *ptr = pcur, *bg, *sm, *lst1, *lst2, i = s1 + s2;

	if (*(a1 + s1 - 1) > *(a2 + s2 - 1)) {
		bg = a1, sm = a2;
		lst1 = a2 + s2, lst2 = a1 + s1;
	} else {
		bg = a2, sm = a1;
		lst1 = a1 + s1, lst2 = a2 + s2;
	}

	for (; sm < lst1; *bg < *sm ? *pcur++ = *bg++ : *pcur++ = *sm++);

	for (; bg < lst2; *pcur++ = *bg++);

	while (i--) *a1++ = *ptr++;

	pcur -= s1 + s2, delete[] pcur, pcur = NULL, ptr = NULL;
}

void mergeSort(int *a, size_t lft, size_t rht) {
	if (rht - lft < 2) return;

	size_t mdl = lft + (rht - lft) / 2;

	mergeSort(a, lft, mdl);
	mergeSort(a, mdl, rht);

	merge(a + lft, mdl - lft, a + mdl, rht - mdl);
}

int main() {
	int a[] = { 9,2,8,17,7,6,15,5,4,3,10}, i; // sample array
	mergeSort(a, 0, Lm(a));

	for (i = 0; i < Lm(a); i++) cout << a[i] << " ";
	cout << " \n";

	system("pause");
}
