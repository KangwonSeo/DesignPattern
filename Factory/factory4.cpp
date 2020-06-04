#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;
struct HotDrink
{
        virtual void prepare(int volume) = 0;
};
 
struct Tea : HotDrink
{
        void prepare(int volume) override
        {
                cout << "Tea" << endl;
        }
};
 
struct Coffee : HotDrink
{
        void prepare(int volume) override
        {
                cout << "Coffee" << endl;
        }
};
 
struct HotDrinkFactory
{
        virtual unique_ptr<HotDrink> make() const= 0;
};
 
struct TeaFactory : HotDrinkFactory
{
        unique_ptr<HotDrink> make() const override 
        {
                return make_unique<Tea>();
        }
};
 
struct CoffeeFactory : HotDrinkFactory
{
        unique_ptr<HotDrink> make() const override 
        {
                return make_unique<Coffee>();
        }
};
 
class DrinkFactory
{
        map<string, function<unique_ptr<HotDrink>()>> factories;
public:
        DrinkFactory()
        {
                factories["tea"] = [] {
                        auto tea = make_unique<Tea>();
                        tea->prepare(200);
                        return tea;
                };
        }
        unique_ptr<HotDrink> make_drink(const string& name)
        {
                return factories[name]();
        }
};
 
int main() {
        DrinkFactory df;
        auto drink = df.make_drink("tea");
        return 0;
}
