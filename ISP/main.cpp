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

struct IPrinter
{
	virtual void print(void) = 0;
};

struct Printer : IPrinter
{
	void print(void) override {
		cout << "print" << endl;
	}
};

struct IMachine : IPrinter {};

struct Machine : IMachine {
	IPrinter& printer;
	Machine(IPrinter& printer) : printer(printer) {};

	void print(void) {
		printer.print();
	}
};
int main(void) {
	IPrinter* p = new Printer;
	IMachine* m = new Machine(*p);
	m->print();

	return 0;
}