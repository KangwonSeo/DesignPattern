#pragma once
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

enum class Color { Red, Green, Blue};
enum class Size { Small, Medium, Large};

struct Product
{
	string name;
	Color color;
	Size size;
	Product(const string& n
		, const Color& c, const Size& s) : name(n)
		, color(c), size(s) {};
};

template <typename T> struct Specification
{
	virtual bool is_satisfied(T* item) = 0;
};
struct ColorSpecification : Specification<Product>
{
	Color color;
	explicit ColorSpecification(const Color color)
		: color{ color } {}
	bool is_satisfied(Product* item) override {
		return item->color == color;
	}
};

template <typename T> struct Filter
{
	virtual vector<T*> filter(
		vector<T*> items,
		Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
	vector<Product*> filter(
		vector<Product*> items,
		Specification<Product>& spec) override
	{
		vector<Product*> result;
		for (auto& p : items)
			if (spec.is_satisfied(p))
				result.push_back(p);
		return result;
	}
};