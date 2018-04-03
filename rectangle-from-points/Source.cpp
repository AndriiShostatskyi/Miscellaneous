#include<iostream>
#include <time.h> 
#include "Rectangle.h"
#include <assert.h>

using namespace std;

void test() {
	double d1, d2;
	vector<point*> points;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
		points.push_back(new point(rand() % 20 + -10, rand() % 20 + -10));

	Rectangle rct1(points); //  One approach of finding two necessary points, with random numbers works correctly most of time in about O(2n)
	rct1.draw_rec();
	d1 = rct1.area();
	
	Rectangle rct2(points, true);// Another approach of finding two necessary points, with random numbers always works correctly in about O(n^2) 
	rct2.draw_rec();
	d2 = rct2.area();
	
	assert(d2 == d1); // Compare areas of 2 rectangles
}

void main() {
	
	for (int i = 0; i < 1000; i++) test(); // run this program a couple of times 

	system("pause");
}
