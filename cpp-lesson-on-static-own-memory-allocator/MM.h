#include<iostream>
#include<list>
#include<stdlib.h> 
#include<algorithm> 
using namespace std;

class MM {
	static char* all_mem;
	static char* position;
	static list<char*> allocated; // container of pointers to allocated memory
	static list<char*> freed;   // container of pointers to freed memory
	static int max_size; 
	MM();
    public:
		static void* getMem(size_t sz); // use to allocate memory
		template <typename T> static void freeMem(T* p)  // use to free memory 
		{
			char *from = (char*)p;
			list<char*>::iterator it;

			// Check if the passed pointer points to the allocated memory
			if(!allocated.empty()) it = find(allocated.begin(), allocated.end(), from -= 4);

			// If yes, remove it from the allocated memory and add to the freed memory
			if (allocated.end() != it)
				freed.push_back(*it), allocated.erase(it);
			else abort();
		}
};

