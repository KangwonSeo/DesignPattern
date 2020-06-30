#include <iostream>
#include <string>
#include <cstdint>
#include <map>
 
using namespace std;

struct Image
{
        virtual void draw() = 0;
};

struct Bitmap : Image
{
        Bitmap(const string& filename)
        {
                cout << "loading image from " << filename << endl;
        }
        void draw() override
        {
                cout << "drawing image " << endl;
        }
};

struct LazyBitmap : Image
{
        LazyBitmap(const string& filename) : filename(filename) {}
        ~LazyBitmap() { delete bmp; }
        void draw() override
        {
                if(!bmp)
                        bmp = new Bitmap(filename);
                bmp->draw();
        }
private:
        Bitmap *bmp{nullptr};
        string filename;
};

int main(void)
{
        LazyBitmap img{ "aa.png" };
        img.draw();
    return 0;
}
