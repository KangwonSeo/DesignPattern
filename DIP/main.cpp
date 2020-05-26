#include <iostream>
#include <memory>

using namespace std;
 
struct ILogger
{
        virtual ~ILogger(){}
        virtual void Log(const string& s) = 0;
};

struct ConsoleLogger : ILogger
{
        ConsoleLogger() {}
        void Log(const string &s) override 
        {
                cout << "LOG" << s.c_str() << endl;
        }
};

struct Car 
{
        shared_ptr<ILogger> logger;
        Car(const shared_ptr<ILogger>& logger) : logger(logger) {
                logger->Log("making car");
        }
};

int main()
{
        Car c(make_shared<ConsoleLogger>());
        return 0;
}
