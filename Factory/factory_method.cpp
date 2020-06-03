#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;
struct Point
{
protected:
        float x, y;
        Point(const float x, const float y) : x(x), y(y) {}
public:
        static Point NewCartesian(float x, float y) {
                return {x,y};
        }
        static Point NewPolar(float x, float y) {
                return {x+1, y+1};
        }
};
int main() {
 
        Point a = Point::NewCartesian(1,2);
        return 0;
}
