#include <iostream>
#include <mutex>

using namespace std;

class Logger
{
    static int count;
    static Logger *loggerInstance;
    static mutex mtx;
    Logger();
    Logger(const Logger &);
    Logger operator=(const Logger &);

public:
    static Logger *getInstance();
    void log(string str);
};