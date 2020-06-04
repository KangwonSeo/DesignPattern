#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
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
        map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
        DrinkFactory()
        {
                hot_factories["coffee"] = make_unique<CoffeeFactory>();
                hot_factories["tea"] = make_unique<TeaFactory>();
        }
        unique_ptr<HotDrink> make_drink(const string& name)
        {
                auto drink = hot_factories[name]->make();
                drink->prepare(200);
                return drink;
        }
};

int main() {
        DrinkFactory df;
        auto drink = df.make_drink("coffee");
        return 0;
}
