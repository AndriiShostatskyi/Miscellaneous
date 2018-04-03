/*
   C++ lesson on static. 
   The task is to make own memory allocator 
*/

#include<iostream>
#include "MM.h"
using namespace std;

void main()
{
	// Trying to allocate and free memory

	int *a = (int*) MM::getMem(10 * sizeof(int));
	cout << a << ' ';
	MM::freeMem(a);

	int *g = (int*)MM::getMem(10 * sizeof(int));
    cout << g << ' ';
	MM::freeMem(g);

	long long *b = (long long*)MM::getMem(30 * sizeof(long long));
	MM::freeMem(b);

	char *c = (char*)MM::getMem(1100 * sizeof(char));
	MM::freeMem(c);

	system("pause");
}