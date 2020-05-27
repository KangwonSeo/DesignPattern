#include <iostream>
#include <vector>
using namespace std;
 
struct HtmlElement
{
        string name;
        string text;
        vector<HtmlElement> elements;
 
        HtmlElement(){}
        HtmlElement(const string& name, const string& text) : name(name), text(text){}
        void str() const {
                cout << name << endl;
                for(auto w : elements)
                        cout << w.name << ", " << w.text << endl;
                cout << name << endl;
        }
};

struct HtmlBuilder
{
        HtmlElement root;
        HtmlBuilder(string root_name) { root.name = root_name; }
        
        void add_child(const string& name, const string& text)
        {
                HtmlElement e{name, text};
                root.elements.emplace_back(e);
        }
        
        void str() { return root.str(); }
};
int main() {
        string words[] = {"hello", "world"};
        HtmlBuilder builder("ul");
        for (auto w: words) 
                builder.add_child("li", w);
        
        builder.str();
        return 0;
}
