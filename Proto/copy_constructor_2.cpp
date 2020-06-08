#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;
struct Address
{
        string street, city;
        Address(const string& street, const string& city) 
        : street(street), city(city){}
};

struct Contact
{
        string name;
        Address *address;
        Contact(const string& name, Address *address) : name(name), address(address){};
        Contact(const Contact& other) :name(other.name), address( new Address(*other.address) ) {}
        //depends default copy construct
};
 
int main() {
        Contact worker{",", new Address{"123", "London"} };
        Contact john = worker;
        john.name = "John";
        cout << john.address->street << endl;
        return 0;
}
