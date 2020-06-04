#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;
struct Point
{
private:
        float x, y;
        Point(float x, float y) : x(x), y(y) {}
        struct PointFactory
        {
        private:
                PointFactory() {}
        public:
                static Point NewCartesian(float x, float y) 
                {
                        return Point{x,y};
                }
                static Point NewPolar(float r, float theta)
                {
                        return Point{r+1,theta+1};
                }
        };      
public:
        static PointFactory Factory;
};

int main() {
        auto a = Point::Factory.NewCartesian(2,3);
        return 0;
}
