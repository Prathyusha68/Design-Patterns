#include "logger.hpp"

using namespace std;

int Logger::count = 0;
Logger *Logger::loggerInstance = nullptr;
mutex Logger::mtx;

Logger::Logger()
{
    count++;
    cout << "Created a Logger Insatnce..." << count << endl;
}

Logger *Logger::getInstance()
{
    if (loggerInstance == nullptr)
    {
        mtx.lock();
        if (loggerInstance == nullptr)
        {
            loggerInstance = new Logger();
        }
        mtx.unlock();
    }
    return loggerInstance;
}

void Logger::log(string str)
{
    cout << str << endl;
}