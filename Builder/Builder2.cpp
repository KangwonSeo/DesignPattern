#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;
class PersonBuilder;
class PersonAddressBuilder;
 
class Person 
{
        string addr, code, city;
        //string company, position;
        Person() {}
 
        friend PersonBuilder;
        friend PersonAddressBuilder;
public:
        static unique_ptr<PersonBuilder> create() {
                return make_unique<PersonBuilder>();
        }
};
 
class PersonBuilderBase
{
protected:
        Person& person;
        explicit PersonBuilderBase(Person& person) : person{person} {}
public:
        operator Person()
        {
                return move(person);
        }
        shared_ptr<PersonAddressBuilder> lives() {
                return make_shared<PersonAddressBuilder>(person);
        }
        //PersonJobBuilder works() const;
};
 
class PersonBuilder : public PersonBuilderBase
{
        Person p;
public:
        PersonBuilder() : PersonBuilderBase{p} {}
};
 
class PersonAddressBuilder : public PersonBuilderBase
{
        typedef PersonAddressBuilder self;
public:
        explicit PersonAddressBuilder(Person& person) : PersonBuilderBase{ person } {}
        self& at(string addr) {
                person.addr = addr;
                return *this;
        }
        self& with(string code) {
                person.code = code;
                return *this;
        }
        self& in(string city) {
                person.city = city;
                return *this;
        }
};
int main() {
        Person p = (*Person::create()).lives()->at("Road").with("128").in("LOONDON");
        return 0;
}
