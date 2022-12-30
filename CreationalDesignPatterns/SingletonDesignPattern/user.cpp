#include <iostream>
#include "logger.hpp"
#include <thread>

using namespace std;

void usr3Fun()
{
    Logger *usr3 = Logger::getInstance();
    usr3->log("Logging this msg from usr 3");
}

void usr4Fun()
{
    Logger *usr4 = Logger::getInstance();
    usr4->log("Logging this msg from usr 4");
}

int main()
{
    thread t1(usr3Fun);
    thread t2(usr4Fun);

    t1.join();
    t2.join();

    Logger *usr1 = Logger::getInstance();
    usr1->log("Logging this msg from usr 1");

    Logger *usr2 = Logger::getInstance();
    usr2->log("Logging this msg from usr 2");
}