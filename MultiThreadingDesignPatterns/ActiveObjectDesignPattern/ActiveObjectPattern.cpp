/**
 * The Active Object Design Pattern is a concurrency pattern used to separate method invocation
 * from method execution, allowing asynchronous and non-blocking behavior.
 */
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
using namespace std;

class ActiveObject
{
private:
    queue<std::function<void()>> que;
    mutex mtx;
    condition_variable cv;
    thread worker_thread;
    bool stop_flag;

public:
    ActiveObject() : stop_flag{false}
    {
        cout << "ActiveObject ctor" << endl;
        worker_thread = std::thread(&ActiveObject::run, this);
    }

    template <class func, class... args>
    void enqueue(func &&f, args &&...arg)
    {
        cout << "Adding task to queue" << endl;
        unique_lock<mutex> lock(mtx);
        que.push(std::bind(forward<func>(f), forward<args>(arg)...));
        lock.unlock();

        cv.notify_all();
        return;
    }

    void run()
    {
        cout << "started worker thread" << endl;
        std::function<void()> task;
        while (1)
        {
            unique_lock<mutex> lock(mtx);

            cv.wait(lock, [this]
                    { return (stop_flag || (!que.empty())); });

            if (stop_flag || que.empty())
            {
                cout << "stop_flag: " << stop_flag << " que size: " << que.size() << endl;
                return;
            }

            task = std::move(que.front());
            que.pop();

            lock.unlock();

            task();
        }
    }

    ~ActiveObject()
    {
        cout << "ActiveObject dtor called" << endl;

        unique_lock<mutex> lock(mtx);

        stop_flag = true;

        lock.unlock();

        cv.notify_all();

        if (worker_thread.joinable())
            worker_thread.join();
    }
};

void add(int a, int b)
{
    cout << "a+b : " << a + b << endl;
}

void sub(int a, int b)
{
    cout << "a-b : " << a - b << endl;
}

void mul(int a, int b)
{
    cout << "a * b : " << a * b << endl;
}

void division(int a, int b)
{
    cout << "a / b : " << a / b << endl;
}

void print(string str)
{
    cout << str << endl;
}

int main()
{
    ActiveObject activeObj;

    activeObj.enqueue(add, 4, 6);
    activeObj.enqueue(sub, 4, 6);
    activeObj.enqueue(mul, 4, 6);
    activeObj.enqueue(division, 4, 6);
    activeObj.enqueue(print, "Hello, world !!!");
    activeObj.enqueue(add, 5, 6);
    activeObj.enqueue(print, "Testing active/actor object pattern");

    std::this_thread::sleep_for(chrono::seconds(2));
    return 0;
}