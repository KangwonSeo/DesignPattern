#include <iostream>
using namespace std;
 
template <class T> 
struct Base
{
    void interface()
    {
        static_cast<T*>(this)->implementation();
        }
};
 
struct Derived : Base<Derived>
{
    void implementation() {
                cout << "impl" << endl;
        }
};
 
int main() {
        Derived d;
        d.interface();
        return 0;
}
