#include <iostream>

using namespace std;

class Professional
{
public:
    // Template method
    // to avoid overriding thsi method in subclasses we can add virtual and final keywords
    // But, in 1st base class this also may not be required just by not adding virtul & final keywaords also works fine
    virtual void dailyRoutine() final
    {
        doWakeUp();
        doEat();
        doWork();
        doSleep();
        cout << endl;
    }

    virtual void doEat() = 0;
    virtual void doWork() = 0;

    void doWakeUp()
    {
        cout << "Wakes up !!" << endl;
    }

    void doSleep()
    {
        cout << "Go to sleep" << endl;
    }
};

class Programmer : public Professional
{
public:
    void doEat()
    {
        cout << "Have a quick snack" << endl;
    }

    void doWork()
    {
        cout << "Writes code !!" << endl;
    }
};

class Doctor : public Professional
{
public:
    void doEat()
    {
        cout << "Eats healthy food" << endl;
    }
    void doWork()
    {
        cout << "Checks patients" << endl;
    }
};

class Chef : public Professional
{
public:
    void doEat()
    {
        cout << "Tastes food and experimenting new receipies" << endl;
    }

    void doWork()
    {
        cout << "Cooks food" << endl;
    }
};

int main()
{
    Programmer programmer;
    cout << "Programmers daily routine" << endl;
    programmer.dailyRoutine();

    Doctor doctor;
    cout << "Doctors daily routine" << endl;
    doctor.dailyRoutine();

    Chef chef;
    cout << "Chefs daily routine" << endl;
    chef.dailyRoutine();

    return 0;
}