#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;
struct Shape
{
        virtual string str() const = 0;
};
struct Circle : Shape
{
        float radius;
        explicit Circle(const float radius) : radius{radius} {}
        void resize(float factor) { radius *= factor; }
        
        string str() const override
        {
                ostringstream oss;
                oss << "A circle of radius " << radius;
                return oss.str();
        }
};

template <typename T> struct ColoredShape : T
{
        static_assert(is_base_of<Shape, T>::value,
                "Template argument must be a Shape");
        //is_base_of<Shape, T>::value should be true
        //if T is derived from Shape, value will be true.
        string color;
        template <typename...Args>
        ColoredShape(const string& color, Args ...args)
                : T(forward<Args>(args)...), color{color} {}
        //parameter pack, means argumens 
        //forward argument to T constructor
        string str() const override
        {
                ostringstream oss;
                oss << T::str() << " has the color " << color;
                return oss.str();
        }
};

int main() {
        ColoredShape<Circle> redCircle{"red", 2};
        cout << redCircle.str() << endl;
        redCircle.resize(0.5);
}

