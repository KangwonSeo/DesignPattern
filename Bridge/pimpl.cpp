#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;

struct Person
{
        string name;
        void greet();
        Person();
        ~Person();
        
        class PersonImpl;
        PersonImpl *impl;
};
struct Person::PersonImpl
{
        void greet(Person* p);
};

Person::Person() : impl(new PersonImpl) {}
Person::~Person() { delete impl; }
void Person::greet()
{
        impl->greet(this);
}
void Person::PersonImpl::greet(Person* p)
{
        cout << "hello" << p->name << endl;
}
int main() {
        Person john;
        john.name = "john";
        john.greet();
}

