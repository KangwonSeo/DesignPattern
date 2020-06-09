#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;
class Database {
public:
        virtual int get_population(const string& name) = 0;
};

class SingletonDatabase : public Database
{
        map<string, int> capitals;
        SingletonDatabase()
        {
                capitals["la"] = 1;
                capitals["lb"] = 2;
                capitals["lc"] = 3;
        }
        
public:
        SingletonDatabase(SingletonDatabase const&) = delete;
        void operator=(SingletonDatabase const&) = delete;
        static SingletonDatabase& get()
        {
                static SingletonDatabase db;
                return db;
        }
        
        int get_population(const string& name) override
        {
                return capitals[name];
        }
};      

class DummyDatabase : public Database
{
        map<string, int> capitals;
public:
        DummyDatabase() 
        {
                capitals["a"] = 1;
                capitals["b"] = 2;
                capitals["c"] = 3;
        }
        int get_population(const string& name) override
        {
                return capitals[name];
        }
};

struct RecordFinder
{
        Database& db;
        explicit RecordFinder(Database& db) : db(db) {}
        int total_population(vector<string> names)
        {
                int result=0;
                for(auto& name : names)
                        result += db.get_population(name);
                return result;
        }
        
};

int main() {
        DummyDatabase db{};
        RecordFinder test{db};
        test.total_population(vector<string>{"a", "b"});
}

