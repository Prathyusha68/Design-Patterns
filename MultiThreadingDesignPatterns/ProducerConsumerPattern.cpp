#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <list>

using namespace std;

list<int> buffer;
int maxBuffSize = 10;
mutex m;
condition_variable cv;

void producer(int count)
{
    while (count)
    {
        unique_lock<mutex> ul(m);
        cv.wait(ul, []
                { return (buffer.size() < maxBuffSize); });

        int val = rand() % 100;
        buffer.push_back(val);
        cout << " Buffer size : " << buffer.size() << " value : " << val << endl;
        count--;
        cv.notify_one();
    }
}

void consumer()
{
    while (1)
    {
        unique_lock<mutex> ul(m);
        cv.wait(ul, []
                { return (buffer.size() != 0); });

        int val = buffer.front();
        cout << " Buffer size : " << buffer.size() << " consumed value : " << val << endl;
        buffer.pop_front();
        cv.notify_one();
    }
}

int main()
{
    srand(time(NULL));
    thread prodThread(producer, 5);
    thread consThread(consumer);

    prodThread.join();
    consThread.join();
}