#include <iostream>
using namespace std;

class IiceCream
{
public:
    virtual void make() = 0;
};

class SimpleIceCream : public IiceCream
{
public:
    void make()
    {
        cout << "Milk + Sugar";
    }
};

class IceCreamDecorator : public IiceCream
{
    IiceCream &decorator;

public:
    IceCreamDecorator(IiceCream &decorator) : decorator{decorator}
    {
    }

    void make()
    {
        decorator.make();
    }
};

class WithFruits : public IceCreamDecorator
{

public:
    WithFruits(IiceCream &decorator) : IceCreamDecorator{decorator}
    {
    }

    void make()
    {
        IceCreamDecorator::make();
        cout << " + Fruits";
    }
};

class WithWafers : public IceCreamDecorator
{
public:
    WithWafers(IiceCream &decorator) : IceCreamDecorator{decorator} {}

    void make()
    {
        cout << " + Wafers";
    }
};

int main()
{
    IiceCream *simpleIceCream = new SimpleIceCream();
    simpleIceCream->make();

    cout << endl;

    IceCreamDecorator *iceCreamDecorator = new WithFruits(*simpleIceCream);
    iceCreamDecorator->make();

    iceCreamDecorator = new WithWafers(*simpleIceCream);
    iceCreamDecorator->make();
}