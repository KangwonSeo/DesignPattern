#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <memory>
#include <functional>
#include <boost/lexical_cast.hpp> 
 
using namespace std;
class Point 
{
public:
    Point() {}
    Point(int x, int y) {}
};

class TextBuffer
{
public:
    TextBuffer(int w, int h) {}
    void add_string(string& str, int idx){}
    int get_size() { return 0; }
};

class Viewport
{
public:
    Viewport(shared_ptr<TextBuffer> buffer) {}
    Viewport(shared_ptr<TextBuffer> buffer, int size, Point& start_p, Point& end_p) {}
};

class Window
{
public:
    Window(const string& title, int w, int h) {}
    vector<shared_ptr<TextBuffer>> buffers;
    vector<shared_ptr<Viewport>> viewports;

    void Show(){};
};

class Console
{
public:
  static Console& instance()
  {
    static Console console;
    return console;
  }

  vector<shared_ptr<Window>> windows;

  // staticÀ¸·Î ¸¸µé ¼ö ¾ø´Ù.
  shared_ptr<Window> single(const string& title, uint8_t charsWide, uint8_t charsHigh)
  {
    auto w = make_shared<Window>(title, charsWide * charWidth, charsHigh * charHeight);
    auto buffer = make_shared<TextBuffer>(charsWide, charsHigh);
    w->buffers.push_back(buffer);
    auto viewport = make_shared<Viewport>(buffer);
    w->viewports.push_back(viewport);
    windows.push_back(w);
    return w;
  }

  shared_ptr<Window> multicolumn(const string& title, uint8_t columnCount, uint8_t columnWidth, uint8_t charsHigh)
  {
    auto w = make_shared<Window>(title, columnCount * columnWidth * charWidth, charsHigh * charHeight);
    for (uint8_t c = 0; c < columnCount; ++c)
    {
      auto buffer = make_shared<TextBuffer>(columnWidth, charsHigh);
      w->buffers.push_back(buffer);
      auto viewport = make_shared<Viewport>(buffer, buffer->get_size(), Point{}, Point{ columnWidth*c, 0 });
      w->viewports.push_back(viewport);
      windows.push_back(w);
    }
    return w;
  }
private:
  const int charWidth = 10, charHeight = 14;
  Console(){}
  Console(Console const&) = delete;
  void operator=(Console const&) = delete;
};
int main(int ac, char* av[])
{
  // 윈도를 하나 만들고 보여준다
  //Window window("Test", 2560, 1440);
  //Window window("Test", 1280, 720);

  //// viewport + buffer를 만들어보자.
  //auto buffer = make_shared<TextBuffer>(40, 40);
  //buffer->add_string("One");
  //buffer->add_string(string("Two"));
  //buffer->add_string(string("Three"));
  //buffer->add_string(string("Four"));
  //buffer->add_string(string("Five"));
  //window.buffers.push_back(buffer);
  //auto viewport = make_shared<Viewport>(buffer);
  //window.viewports.emplace_back(viewport);

  //auto viewport2 = make_shared<Viewport>(buffer, Size{ 40,40 }, Point{}, Point{ 45, 0 });
  //window.viewports.emplace_back(viewport2);
  //
  //auto viewport3 = make_shared<Viewport>(buffer, Size{ 40,40 }, Point{}, Point{ 90, 0 });
  //window.viewports.emplace_back(viewport3);

  //auto window = Console::instance().single("Test", 50, 30);
  auto window = Console::instance().multicolumn("Test", 2, 40, 40);

  for (size_t i = 0; i < 40; i++)
  {
    window->buffers[1]->add_string(
      string("This is line ") + boost::lexical_cast<string>(i),
      (i % 2 == 0));
  }

  window->Show();
  return 0;
}


