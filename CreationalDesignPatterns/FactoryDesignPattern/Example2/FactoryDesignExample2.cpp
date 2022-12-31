#include <iostream>
using namespace std;

class IVehicleFactory
{
public:
    static IVehicleFactory *createVehicle(int type);
    virtual void startEngine() = 0;
};

class Bike : public IVehicleFactory
{
public:
    Bike()
    {
        cout << "Bike class" << endl;
    }

    void startEngine()
    {
        cout << "Bike engine started..." << endl;
    }
};

class Car : public IVehicleFactory
{
public:
    Car()
    {
        cout << "Car class" << endl;
    }

    void startEngine()
    {
        cout << "Car engine started..." << endl;
    }
};

IVehicleFactory *IVehicleFactory ::createVehicle(int type)
{
    switch (type)
    {
    case 1:
        return new Bike();
        break;
    case 2:
        return new Car();
        break;
    default:
        cout << "Invalid type, re-enter the type" << endl;
        return nullptr;
    }
}

int main()
{
    while (1)
    {
        int type;
        cout << "Enter type Bike (1) Car(2) Exist(0)" << endl;
        cin >> type;
        if (!type)
            break;

        IVehicleFactory *obj = IVehicleFactory::createVehicle(type);
        if (obj)
        {
            obj->startEngine();
            delete obj;
        }
    }

    cout << "Exist.." << endl;
}