#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <future>

using namespace std;

class ThreadPool
{
private:
    int numOfThreads;
    vector<std::thread> threads;
    mutex mtx;
    condition_variable cv;
    queue<function<void()>> que;
    bool stop;

public:
    ThreadPool(int numOfThreads) : numOfThreads(numOfThreads)
    {
        for (int i = 0; i < numOfThreads; i++)
        {
            // Use emplace_back when you want to construct elements directly in the container without creating them beforehand.
            threads.emplace_back([this]
                                 {
                function<void()> task;
                while(1)
                {
                    unique_lock<mutex> lock(mtx);

                    cv.wait(lock, [this]
                            { return (stop || (!que.empty())); });

                    if(stop || que.empty())
                    {
                        return;
                    }

                    task = move(que.front());
                    que.pop();

                    lock.unlock();

                    task();

                } });
        }
    }

    ~ThreadPool()
    {
        unique_lock<mutex> lock(mtx);
        stop = true;
        lock.unlock();

        cv.notify_all();

        for (auto &th : threads)
        {
            th.join();
        }
    }

    /*
     * With the trailing return type syntax, you can specify the return type of a function after the parameter list
     * using the auto keyword and the trailing -> arrow. This allows you to use expressions and decltype to deduce
     * the return type based on the function’s implementation.
     */

    template <class F, class... Args>
    auto submitTask(F &&func, Args &&...args) -> future<decltype(func(args...))>
    {
        using return_type = decltype(func(args...));

        // The main advantage of a packaged task is that it can link a callable object to a future
        auto task = make_shared<packaged_task<return_type()>>(bind(forward<F>(func), forward<Args>(args)...));

        future<return_type> res = task->get_future();

        unique_lock<mutex> lock(mtx);

        // Use emplace when you want to construct elements directly in the container without creating them beforehand.
        que.emplace([task]
                    { (*task)(); });

        lock.unlock();

        cv.notify_one();

        return res;
    }
};

void func1()
{
    cout << "This function has no args and void return type : " << this_thread::get_id() << endl;
    // this_thread::sleep_for(chrono::seconds(2));
    return;
}

int func2(int a, int b)
{
    cout << "This function has 2 args and int return type : " << this_thread::get_id() << endl;

    return a + b;
}

int main()
{
    ThreadPool pool(4);

    while (1)
    {
        pool.submitTask(func1);
        future<int> res = pool.submitTask(func2, 4, 6);
    }

    // cout << "func2 o/p : " << res.get() << endl;
    return 0;
}