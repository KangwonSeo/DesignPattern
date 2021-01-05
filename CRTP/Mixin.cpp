#include <iostream>
using namespace std;

struct A1 {
public:
        int x{123};
};
template <typename T> 
struct A2 : T {};
template <typename T> 
struct A3 : T {
        void foo() {
                cout << T::A1::x << endl;
        }
};

int main() {
        A3<A2<A1>> A;
        A.foo();

        return 0;
}
