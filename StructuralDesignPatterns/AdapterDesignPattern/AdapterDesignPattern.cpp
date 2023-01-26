/**
 * Adapter is a structural design pattern that allows objects with incompatible interfaces to collaborate.
 */
#include <iostream>
using namespace std;

class Target
{
public:
    void processData(string data)
    {
        cout << "Processing " << data << " data" << endl;
    }
};

class Adaptee
{
public:
    void processData(string data)
    {
        if (data.compare("JSON") == 0)
        {
            cout << "Processing " << data << " data" << endl;
        }
        else
        {
            cout << "The data format received cannot be handled" << endl;
        }
    }
};

class Adapter : public Target
{
    Adaptee *adapt = NULL;

public:
    Adapter()
    {
        if (adapt == NULL)
        {
            adapt = new Adaptee();
        }
    }

    ~Adapter()
    {
        delete adapt;
    }

    void processData(string data)
    {
        cout << "Converting XML to JSON data" << endl;
        data = "JSON";
        adapt->processData(data);
    }
};

int main()
{
    Target *target = new Target();
    target->processData("XML");

    cout << endl;

    Adaptee *adapt = new Adaptee();
    adapt->processData("XML");

    cout << endl;

    Adapter *tarAdapt = new Adapter();
    tarAdapt->processData("XML");
}