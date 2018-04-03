#include<iostream>
#include<vector>
#include <assert.h>
using namespace std;

struct point {
	double x, y;
	point() :x(0), y(0) {}
	point(double x, double y) : x(x), y(y) {}
	void show() { cout << x << ' ' << y << endl; }
};

class Rectangle {
	point p1, p2; // It's enough to have 2 points to obtain all points of the biggest rectangle
public:
	Rectangle(vector<point*> &pnts);
	Rectangle(vector<point*> &pnts, bool brute_force);
	void Rectangle::draw_rec();
	double area() { return abs(p1.x - p2.x) * abs(p1.y - p2.y); }
};
