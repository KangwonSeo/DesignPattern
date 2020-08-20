#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include <algorithm>
using namespace std;
 
struct Person;

struct PersonListener
{
  virtual ~PersonListener() = default;
  virtual void person_changed(Person& p, const string& property_name, const int new_value) = 0;
};
static mutex mtx;

struct Person
{
  explicit Person(int age)
    : age(age)
  {
  }

  int get_age() const
  {
    return age;
  }

  void set_age(const int age);

  bool get_can_vote() const
  {
    return age >= 16;
  }

  void subscribe(PersonListener* pl);
  void unsubscribe(PersonListener* pl);
  void notify(const string& property_name, const int new_value);
private:
  int age;
  vector<PersonListener*> listeners;
};

void Person::set_age(const int age)
{
  if (this->age == age) return;

  int old_c_v = get_can_vote();

  this->age = age;
  notify("age", this->age);

  int new_c_v = get_can_vote();
  if (old_c_v != new_c_v)
  {
    notify("can_vote", new_c_v);
  }
}

void Person::subscribe(PersonListener* pl)
{
  lock_guard<mutex> guard{ mtx };
  if (find(begin(listeners), end(listeners), pl) == end(listeners))
    listeners.push_back(pl);
}

void Person::unsubscribe(PersonListener* pl)
{
  lock_guard<mutex> guard{ mtx };
  if (listeners.empty()) return;
  for (auto it = listeners.begin(); it != listeners.end(); ++it)
  {
        if (*it == pl) *it = nullptr;
  }

}

void Person::notify(const string& property_name, const int new_value)
{
  lock_guard<mutex> guard{ mtx };       
  for (const auto listener : listeners)
        if(listener)
      listener->person_changed(*this, property_name, new_value);
    listeners.erase(
          remove(listeners.begin(), listeners.end(), nullptr),
          listeners.end());
}

struct ConsoleListener : PersonListener
{
  void person_changed(Person& p, const string& property_name, const int new_value) override
  {
    cout << "person's " << property_name << " has been changed to ";
    if (property_name == "age")
    {
      cout << new_value << endl;
    }
    else if (property_name == "can_vote")
    {
      cout << new_value << endl;
    }
    cout << "\n";
  }
};
 
int main()
{
  Person p{ 14 };
  ConsoleListener cl;
  p.subscribe(&cl);
  p.subscribe(&cl); // 무시된다
  p.set_age(15);
  p.set_age(16);
  p.unsubscribe(&cl);
  p.set_age(17);

  getchar();
  return 0;
}
