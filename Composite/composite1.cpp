#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

struct GraphicObject
{
        virtual void draw() = 0;
};
struct Circle : GraphicObject
{
        void draw() override
        {
                cout << "Circle" << endl;
        }
};
struct Group : GraphicObject
{
        string name;
        explicit Group(const string& name) : name{name} {}
        void draw() override
        {
                cout << "Group" << endl;
                for (auto&& o : objects)
                        o->draw();
        }
        vector<GraphicObject*> objects;
};

int main() {
        Group root("root");
        Circle c1, c2;
        root.objects.push_back(&c1);
        
        Group subgroup("sub");
        subgroup.objects.push_back(&c2);
        
        root.objects.push_back(&subgroup);
        root.draw();
}
