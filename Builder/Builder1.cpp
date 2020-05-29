#include <iostream>
#include <vector>
#include <memory>
using namespace std;
struct HtmlBuilder;
struct HtmlElement
{
        string name;
        string text;
        vector<HtmlElement> elements;
        void str() const {
                cout << name << endl;
                for(auto w : elements)
                        cout << w.name << ", " << w.text << endl;
                cout << name << endl;
        }
        static unique_ptr<HtmlBuilder> build(const string& root_name) {
                return make_unique<HtmlBuilder>(root_name);
        }
protected:
        HtmlElement(){}
        HtmlElement(const string& name, const string& text) : name(name), text(text){}
 
};
 
struct HtmlBuilder
{
        HtmlElement root;
        HtmlBuilder(string root_name) { root.name = root_name; }
 
        HtmlBuilder& add_child(const string& name, const string& text)
        {
                HtmlElement e{name, text};
                root.elements.emplace_back(e);
                return *this;
        }
 
        void str() { return root.str(); }
};
int main() {
        auto builder = HtmlElement::build("ul");
        //builder.add_child("li", "hello").add_child("li", "world");
        //builder.str();
        return 0;
}
