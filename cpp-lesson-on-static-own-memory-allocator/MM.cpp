#include "MM.h"

char* MM::all_mem = nullptr;
char* MM::position = nullptr;
int MM::max_size = 1000;
list<char*> MM::allocated;
list<char*> MM::freed;

MM::MM() 
{
	all_mem = new char[max_size];
	position = all_mem;
}

void* MM::getMem(size_t sz)
{
	// Check if it's the first call
	if (!all_mem) MM();

	char *ptr; list<char*>::iterator it;

	// Try to find enough memory in the freed memory
	if (!freed.empty()) it = find_if(freed.begin(), freed.end(), [sz](char*p) { return sz <= *((int*)p); });
	
	if (!freed.empty() && freed.end() != it) { // If found, allocate from there
		ptr = *it;
		freed.erase(it);
		allocated.push_back(ptr);
		ptr += 4;
	}
	else { // allocate from all_mem
		if ((position + sz + 4) >= (all_mem + max_size)) { // Check if all_mem has enough memory and, if no, reallocate
			int how_far = position - all_mem;
			max_size += 1000;
			all_mem = (char*)realloc(all_mem, max_size);
			position = all_mem;
			position += how_far;
		}
		ptr = position;
		position += 4 + sz;
		*((int*)ptr) = sz;
		allocated.push_back(ptr);
		ptr += 4;
	}
	return (void*)ptr;
}

