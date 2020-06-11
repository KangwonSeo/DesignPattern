#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

struct Creature
{
        enum Abilities { str, spe, count };
        array<int, count> abilities;
        int get_strength() const { return abilities[str]; }
        void set_strength(int value) { abilities[str] = value; }
        
        int get_speed() const { return abilities[spe]; }
        void set_speed(int value) { abilities[spe] = value; }
        
        int sum() const {
                return accumulate(abilities.begin(), abilities.end(), 0);
        }
        double average() const {
                return sum() / (double)count;
        }
        int max() const {
                return *max_element(abilities.begin(), abilities.end());
        }
};

int main() {
        Creature c;
        c.set_strength(10);
        c.set_speed(20);
        cout << c.average() << endl;
}

