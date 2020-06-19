#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;

struct Logger
{
        function<void()> func;
        string name;
        
        Logger(const function<void()>& func, const string& name)
                : func{func}, name{name} {}
        void operator()() const
        {
                cout << "Enter " << name << endl;
                func();
                cout << "Exiting " << name << endl; 
        }
};

int main() {
        Logger([]() {cout << "Hello" << endl;}
        , "HelloFunction")();
}

