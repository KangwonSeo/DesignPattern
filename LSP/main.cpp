#if 1
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cstring>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <numeric>
#include <math.h>
#define pii pair<int, int> 
#define pb push_back
#define mp make_pair
#define INF 987654321
using namespace std;
#endif
class Rectangle
{
protected:
	int width, height;
public:
	Rectangle(const int width, const int height)
		: width(width), height(height) {}

	int get_width() const { return width; }
	int get_height() const { return height; }
	virtual void set_width(const int width) { 
		this->width = width; 
	}
	virtual void set_height(const int height) {
		this->height = height;
	}
	int area() const { return width * height; }
};

class Square : public Rectangle
{
public:
	Square(int size) : Rectangle(size, size) {}
	void set_width(const int width) override {
		this->width = height = width;
	}
	void set_height(const int height) override {
		this->height = width = height;
	}
};

void process(Rectangle& r)
{
	int w = r.get_width();
	cout << w << endl;
	r.set_height(10);
	cout << r.get_width() << endl;
	cout << r.get_height() << endl;
	cout << r.area() << endl;
}
int main(void)
{
	Square s{ 5 };
	process(s);
}
