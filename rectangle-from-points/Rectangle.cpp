#include"Rectangle.h"

// Based on primitive brute force algorithm (about O(n^2)) for finding 2 points 
// that can form a rectangle with the largest area
Rectangle::Rectangle(vector<point*> &pnts, bool brute_force){
	double a = 0, b = 0, s = 0;
	for (int i = 0, j; i < pnts.size(); i++) {
		for (j = i + 1; j < pnts.size(); ++j) {
			a = abs(pnts[i]->x - pnts[j]->x), b = abs(pnts[i]->y - pnts[j]->y);
			if (s < a*b) {
				s = a*b, p1 = *pnts[i], p2 = *pnts[j];
			}
		}
	}
}

// Tried to figure out a more efficient (much better than O(n^2)) algorithm compared to the one above.
// The one below is based on finding the farthest point and runs in about O(2n) and works 
// correctly most of the time, but raraly does it give wrong results, which is an 
// interesting property (i.e. the farthest point does not always promise the largest area.
// It seems that I cannot come up with such an algorithm. 
// Convex hull, I think, also wouldn't make much difference:
// http://www.tcs.fudan.edu.cn/rudolf/Courses/Algorithms/Alg_ss_07w/Webprojects/Qinbo_diameter/2d_alg.htm 
// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#Python
// Sorting points also is not an option.

Rectangle::Rectangle(vector<point*> &pnts) {
	double dst = 0, a = 0, b = 0, s = 0, tmp = 0; int i;

	// 1. Find the point that's most distant from O (origin)
	for (p1 = *pnts[0], i = 1; i < pnts.size(); i++)  
		if (abs(pnts[i]->x * pnts[i]->y) > abs(p1.x * p1.y)) p1 = *pnts[i];

	// 2. Find the point that together with the most distant point form a rectangle with the largest area
	for (i = 0; i < pnts.size(); i++) {
		a = abs(pnts[i]->x - p1.x), b = abs(pnts[i]->y - p1.y);
		if (s < a*b) s = a*b, p2 = *pnts[i];
	}

}
// For testing purpose
void Rectangle::draw_rec() {
	cout << " s = " << abs(p1.x - p2.x) * abs(p1.y - p2.y) << endl;
	cout << "  ";
	for (int i = 0; i < abs(p1.x - p2.x); i++) {
		cout << "-";
	} cout << endl;
	for (int i = 0, j; i < abs(p1.y - p2.y); i++) {
		cout << ' ' << "|";
		for (j = 0; j < abs(p1.x - p2.x); j++) cout << ' ';
		cout << "|" << endl;
	}
	cout << "  ";
	for (int i = 0; i < abs(p1.x - p2.x); i++) {
		cout << "-";
	} cout << endl;
}

