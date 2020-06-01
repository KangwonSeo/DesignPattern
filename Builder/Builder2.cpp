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
        
        friend class PersonBuilder;
public:
        static PersonBuilder create(void) {
                PersonBuilder e = PersonBuilder();
                return e;
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
        PersonAddressBuilder lives() const;
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
        Person p = Person::create().lives().at("Road").with("128").in("LOONDON");
        return 0;
}
