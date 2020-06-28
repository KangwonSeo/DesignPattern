#include <iostream>
#include <string>
#include <cstdint>
#include <map>

using namespace std;
typedef uint32_t key;

struct User
{
    User(const string& first_name, const string& last_name)
        : first_name{ add(first_name) }, last_name{ add(last_name) }
    {
    }

    const string& get_first_name() const
    {
        return names[first_name];
    }

    const string& get_last_name() const
    {
        return names[last_name];
    }

    static void info()
    {
        for (auto entry : names)
        {
            cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
        }
    }

    friend ostream& operator<<(ostream& os, const User& obj)
    {
        return os
            << "first_name: " << obj.first_name << " " << obj.get_first_name()
            << " last_name: " << obj.last_name << " " << obj.get_last_name();
    }

protected:
    static map<key, string> names;
    static key seed;

    static key add(const string& s)
    {
        map<key, string>::iterator i;
        for (i = names.begin(); i != names.end(); i++) {
            if (!s.compare(i->second)) break;
        }
        if (i == names.end()) {
            key id = ++seed;
            names.insert({ id, s });
            return id;
        }
        else {
            return i->first;
        }
    }
    key first_name, last_name;
};

key User::seed = 0;
map<key, string> User::names{};

int main(void)
{
    return 0;
}