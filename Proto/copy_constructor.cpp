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
        Contact(const Contact& other) :name(other.name)
        {
                address = new Address(
                        other.address->street, other.address->city
                );
        }
};
 
int main() {
        Address def = Address{"123", "London"};
        Contact worker{",", &def };
        Contact john = worker;
        john.name = "John";
        return 0;
}
