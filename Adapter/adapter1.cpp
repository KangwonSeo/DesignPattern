#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;

struct Point
{
        int x,y;
};
struct Line
{
        Point start, end;
};
struct VectorObject
{
        virtual vector<Line>::iterator begin() = 0;
        virtual vector<Line>::iterator end() = 0;
};
struct VectorRectangle : VectorObject
{

        VectorRectangle(int x, int y, int width, int height)
        {
                lines.emplace_back(Line{ Point{x,y}, Point{x+width,y} });
                lines.emplace_back(Line{ Point{x+width,y}, Point{x+width,y+height} });
                lines.emplace_back(Line{ Point{x,y}, Point{x,x,y+height} });
                lines.emplace_back(Line{ Point{x,y+height}, Point{x+width,y+height} });
        }
        
        vector<Line>::iterator begin() override {
                return lines.begin();
        }
        vector<Line>::iterator end() override {
                return lines.end();
        }
private:
        vector<Line> lines;
};

struct LineToPointAdapter
{
        typedef vector<Point> Points;
        LineToPointAdapter(Line& line)
        {
                int left = min(line.start.x, line.end.x);
                int right = max(line.start.x, line.end.x);
                int top= min(line.start.x, line.end.x);
                int bottom= min(line.start.y, line.end.y);
                int dx = right - left;
                int dy = line.end.y - lien.start.y;
                if (dx == 0)
                {
                        for (int y = top; y <=bottom; ++y)
                                points.emplace_back(Point {left,y});
                } else if (dy == 0) 
                {
                        for (int x = left; y <=right; ++x)
                                points.emplace_back(Point {x,top});
                }
        }
        Points::iterator begin() { return points.begin(); }
        Points::iterator begin() { return points.begin(); }
private:
        Points points;
};
int main() {
        vector<shared_ptr<VectorObject> > vectorObjects {
                make_shared<VectorRectangle>(10,10,100,100),
                make_shared<VectorRectangle>(30,30,60,60)
        };
        for (auto& obj : vectorObjects)
        {
                for (auto& line : *obj) {
                        LineToPointAdapter lpo{ line };
                        //DrawPoints(dc, lpo.begin(), lpo.end());
                }
        }
}

