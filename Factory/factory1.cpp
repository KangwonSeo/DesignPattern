#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;
struct Point
{
        float x, y;
        friend class PointFactory;
private:
        Point(float x, float y) : x(x), y(y) {}
};
 
struct PointFactory
{
        static Point NewCartesian(float x, float y) 
        {
                return Point{x,y};
        }
        static Point NewPolar(float r, float theta)
        {
                return Point{r+1,theta+1};
        }
};
 
int main() {
        auto a = PointFactory::NewCartesian(1,2);
        return 0;
}
