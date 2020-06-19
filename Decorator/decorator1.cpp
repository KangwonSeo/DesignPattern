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
struct ColoredShape : Shape
{
        Shape& shape;
        string color;
        
        ColoredShape(Shape& shape, const string& color)
                : shape{shape}, color{color} {}
        
        string str() const override
        {
                ostringstream oss;
                oss << shape.str() << " has the color " << color;
                return oss.str();
        }
        
};
int main() {
        Circle circle{0.5f};
        ColoredShape redCircle{circle, "red"};
        cout << redCircle.str();
}

