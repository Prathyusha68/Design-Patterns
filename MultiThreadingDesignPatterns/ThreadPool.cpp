#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

mutex m;
condition_variable cv;
vector<thread> workerThreads;
/*
 * SUM = 1
 * Substraction = 2
 * Multiplication = 3
 * Division = 4
 */
typedef struct Task
{
    int a;
    int b;
    int flag;
} Task;
queue<Task> taskQueue;

void submitTask(Task task)
{
    unique_lock<mutex> qLock(m);
    cout << "Queueing the task.." << task.flag << endl;
    taskQueue.push(task);
    cv.notify_one();
}

void processTheTask(Task task)
{
    //this_thread::sleep_for(chrono::seconds(5));
    switch (task.flag)
    {
    case 1:
        cout << "Addition of a and b is : " << (task.a + task.b) << " thread id : " << this_thread::get_id() << endl;
        break;
    case 2:
        cout << "Substration of a and b is : " << (task.a - task.b) << " thread id : " << this_thread::get_id() << endl;
        break;
    case 3:
        cout << "Multiplication of a and b is : " << (task.a * task.b) << " thread id : " << this_thread::get_id() << endl;
        break;
    case 4:
        cout << "Division of a and b is : " << (task.a / task.b) << " thread id : " << this_thread::get_id() << endl;
        break;
    default:
        cout << "Default case " << task.flag << endl;
        break;
    }
}

void workerThreadFunc()
{
    while (1)
    {
        Task task;
        {
            unique_lock<mutex> wLock(m);
            cv.wait(wLock, []
                    { return (!taskQueue.empty()); });

            task = taskQueue.front();
            taskQueue.pop();
            cout << "processing the task.." << task.flag << " thread id : " << this_thread::get_id() << endl;
        }
        processTheTask(task);
    }
}

int main()
{
    int numOfThreads = thread::hardware_concurrency();
    cout << "Num of threads : " << numOfThreads << endl;
    for (auto i = 0; i < numOfThreads; i++)
    {
        workerThreads.push_back(thread(workerThreadFunc));
    }

    Task sum;
    sum.a = 5, sum.b = 6, sum.flag = 1;
    submitTask(sum);

    Task sub;
    sub.a = 9, sub.b = 6, sub.flag = 2;
    submitTask(sub);

    Task mul;
    mul.a = 5, mul.b = 6, mul.flag = 3;
    submitTask(mul);

    Task div;
    div.a = 30, div.b = 6, div.flag = 4;
    submitTask(div);

    for (auto &thread : workerThreads)
    {
        if (thread.joinable())
            thread.join();
    }
}