#include <iostream>
using namespace std;

struct foo {
        int a;
};
struct test {
        foo root;
        operator foo() { 
                cout << "foo" << endl;
                return root; 
        } 
};
int main() {
        test c;
        foo b = c;
        return 0;
}
