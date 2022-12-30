#include <iostream>
using namespace std;

class AC
{
public:
    void acOn()
    {
        cout << "AC is ON" << endl;
    }

    void acOff()
    {
        cout << "AC is OFF" << endl;
    }
};

class Alarm
{
public:
    void alarmOn()
    {
        cout << "Alarm is ON" << endl;
    }

    void alarmOff()
    {
        cout << "Alarm is OFF" << endl;
    }
};

class TV
{
public:
    void tvOn()
    {
        cout << "TV is ON" << endl;
    }

    void tvOff()
    {
        cout << "TV is OFF" << endl;
    }
};

class HouseFacade
{
    Alarm alarm;
    TV tv;
    AC ac;

public:
    void goToOffice()
    {
        cout << "Going to Office.." << endl;
        alarm.alarmOn();
        ac.acOff();
        tv.tvOff();
    }

    void cameHome()
    {
        cout << "Came Home.." << endl;
        alarm.alarmOff();
        tv.tvOn();
        ac.acOn();
    }
};

int main()
{
    HouseFacade *houseFacade = new HouseFacade();
    houseFacade->goToOffice();
    cout << endl;
    houseFacade->cameHome();
}