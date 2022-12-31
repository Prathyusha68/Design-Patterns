#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class SingletonPattern
{
private:
    static mutex mtx;
    static SingletonPattern *singletonInstance;
    SingletonPattern();
    SingletonPattern(const SingletonPattern &);
    SingletonPattern &operator=(const SingletonPattern &);

public:
    ~SingletonPattern();
    static SingletonPattern *getInstance();
    void func();
};

SingletonPattern *SingletonPattern::singletonInstance = NULL;
mutex SingletonPattern::mtx;
SingletonPattern::SingletonPattern()
{
    cout << "Constructor of SingletonPattern class" << endl;
}

SingletonPattern::~SingletonPattern()
{
    cout << "Destructor of SingletonPattern class" << endl;
}

SingletonPattern *SingletonPattern::getInstance()
{
    if (singletonInstance == NULL)
    {
        mtx.lock();
        if (singletonInstance == NULL)
        {
            singletonInstance = new SingletonPattern();
        }
        mtx.unlock();
    }
    return singletonInstance;
}

void SingletonPattern::func()
{
    cout << "func() of Singleton Class.." << endl;
}

void threadFun()
{
    SingletonPattern *singleInstance = SingletonPattern::getInstance();
    singleInstance->func();
}

int main()
{
    thread t1(threadFun);
    thread t2(threadFun);

    SingletonPattern *singleInstance1 = SingletonPattern::getInstance();
    singleInstance1->func();

    SingletonPattern *singleInstance2 = SingletonPattern::getInstance();
    singleInstance2->func();

    t1.join();
    t2.join();

    /**
     * static objects are allocated storage in static storage area. static object is destroyed at the
     * termination of program
     */
}