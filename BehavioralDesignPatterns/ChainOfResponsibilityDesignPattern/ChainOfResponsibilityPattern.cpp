#include <iostream>
using namespace std;

enum class LogLevel
{
    DEBG,
    INFO,
    ERRO
};

class Logger
{
protected:
    Logger *nextLogger;

public:
    Logger(Logger *nextLogger) : nextLogger{nextLogger} {}

    virtual void Log(LogLevel lvl, string message) = 0;
};

class InfoLogger : public Logger
{
public:
    InfoLogger(Logger *nextLogger) : Logger{nextLogger} {}

    void Log(LogLevel lvl, string message)
    {
        if (lvl == LogLevel::INFO)
        {
            cout << "[INFO] : " << message.c_str() << endl;
        }
        else
        {
            nextLogger->Log(lvl, message);
        }
    }
};

class DebugLogger : public Logger
{
public:
    DebugLogger(Logger *nextLogger) : Logger{nextLogger} {}

    void Log(LogLevel lvl, string message)
    {
        if (lvl == LogLevel::DEBG)
        {
            cout << "[DEBG] : " << message.c_str() << endl;
        }
        else
        {
            nextLogger->Log(lvl, message);
        }
    }
};

class ErrorLogger : public Logger
{
public:
    ErrorLogger() : Logger{NULL} {}

    void Log(LogLevel lvl, string message)
    {
        if (lvl == LogLevel::ERRO)
        {
            cout << "[ERRO] : " << message.c_str() << endl;
        }
    }
};

int main()
{
    Logger *pErroLog = new ErrorLogger();
    Logger *pInfoLog = new InfoLogger(pErroLog);
    Logger *pDebgLog = new DebugLogger(pInfoLog);

    // Log messages at same level
    pInfoLog->Log(LogLevel::INFO, "Info log message at INFO lvl");
    pDebgLog->Log(LogLevel::DEBG, "Debug log message at DEBG lvl");
    pErroLog->Log(LogLevel::ERRO, "Error log message at ERRO lvl");

    // chain is DEBG->INFO->ERRO
    pDebgLog->Log(LogLevel::INFO, "log message at INFO lvl called with DEBG object");
    pDebgLog->Log(LogLevel::ERRO, "log message at ERRO lvl called with DEBG object");
    pInfoLog->Log(LogLevel::ERRO, "log message at ERRO lvl called with INFO object");

    return 0;
}