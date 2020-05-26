#include <iostream>
using namespace std;
 
struct Engine {
        float volume;
        friend ostream& operator<<(ostream& os, const Engine& obj) {
                return os << "volume: " << obj.volume << endl;
        }
};
int main() {
        // your code goes here
        Engine e;
        e.volume = 0.5;
        cout << e;
        return 0;
}
