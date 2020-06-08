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
};

struct EmployeeFactory
{
        static Contact main;
        static Contact aux;
        
        static unique_ptr<Contact> NewMainOfficeEmployee(string name) {
                return NewEmployee(name, main);
        }
        
        static unique_ptr<Contact> NewAuxOfficeEmployee(string name) {
                return NewEmployee(name, aux);
        }
private:
        static unique_ptr<Contact> NewEmployee(string name, Contact& proto) {
                auto result = make_unique<Contact>(proto);
                result->name = name;
                return result;
        }
};      
int main() {
        EmployeeFactory::main(" ", new Address("123", "London"));
        EmployeeFactory::aux(" ", new Address("123", "London"));
        //Contact main(" ", new Address("123", "London"));
        //Contact aux(" ", new Address("456", "London"));
        
        auto john = EmployeeFactory::NewAuxOfficeEmployee("John");
        return 0;
}
