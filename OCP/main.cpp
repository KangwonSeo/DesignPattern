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
#include "Product.h"
int main(void)
{
	vector<Product*> vin;
	vector<Product*> vout;
	Product p1("one", Color::Green, Size::Small);
	Product p2("two", Color::Red, Size::Small);
	vin.push_back(&p1);
	vin.push_back(&p2);
	BetterFilter bf;
	ColorSpecification green(Color::Green);

	vout = bf.filter(vin, green);
	for (auto& i : vout) {
		cout << i->name << endl;
	}
}
