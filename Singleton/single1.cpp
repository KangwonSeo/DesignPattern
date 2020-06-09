#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <functional>
 
using namespace std;
struct Database {
protected:
        Database() {}
public:
        static Database* get()
        {
                static Database* database = new Database();
                return database;
        }
        Database(Database const&) = delete;
        Database(Database&&) = delete;
        Database& operator=(Database const&) = delete;
        Database & operator=(Database &&) = delete;
};
 
int main() {
        Database *b = Database::get();
        return 0;
}
