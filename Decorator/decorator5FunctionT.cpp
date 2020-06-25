#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;

template <typename> struct Logger3;
//base template
template <typename R, typename... Args>
//템플릿 부분 특수화, 해당 template의 경우 이 클래스.
struct Logger3<R(Args...)>
{
        function<R(Args ...)> func;
        //function<return(arg)>
        string name;
        
        Logger3(function<R(Args ...)> func, const string& name)
                : func{func}, name{name}{}
        R operator()(Args ...args) const
        {
                cout << "Enter " << name << endl;
                R result = func(args...);
                cout << "Exiting " << name << endl;
                return result;
        }
};
template <typename R, typename... Args> 
//가변길이 템플릿
auto make_logger3(R (*func)(Args...), const string& name)
{
        return Logger3<R(Args...)>( function<R(Args...)>(func), name);
}


double add(double a, double b)
{
        cout << a << "+" << b << "=" << (a+b) << endl;
        return a+b;
}

int main() {
        auto logged_add = make_logger3(add, "Add");
        auto result = logged_add(2,3);
}

