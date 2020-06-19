#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;

template <typename Func>
struct Logger2
{
        Func func;
        string name;
        
        Logger2(const Func& func, const string & name)
                : func{func}, name{name}{}
        void operator()() const
        {
                cout << "Enter " << name << endl;
                func();
                cout << "Exiting " << name << endl; 
        }
};
template <typename Func> auto make_logger2(Func func, const string& name)
{
        return Logger2<Func>{ func, name };
}
// template function didn't need to declare type in call
int main() {
        auto call = make_logger2([]() { cout << "Hello!" << endl; },
                "HelloFunction");
        call();
}

