#include <iostream>
#include <unordered_map>

using namespace std;

enum ProtoType
{
    CAR,
    BIKE
};

class ToyPrototype
{
public:
    ToyPrototype()
    {
        cout << "ToyPrototype constructor !!!" << endl;
    }

    virtual ToyPrototype *clone() = 0;
};

class Car : public ToyPrototype
{
    int data;

public:
    Car(int data) : data{data}
    {
        cout << "Car constructor !!!" << endl;
    }

    // Copy constructor to perform deep copy
    Car(const Car &obj) : data{obj.data}
    {
        cout << "[Copy Constrictor] Car prototype created !!!" << endl;
    }

    // Clone function to create a new instance of the same class
    ToyPrototype *clone()
    {
        return new Car(*this);
    }
};

class Bike : public ToyPrototype
{
    int data;

public:
    Bike(int data) : data{data}
    {
        cout << "Bike constructor !!!" << endl;
    }

    // Copy constructor to perform deep copy
    Bike(const Bike &obj) : data{obj.data}
    {
        cout << "[Copy Constrictor] Bike prototype created !!!" << endl;
    }

    // Clone function to create a new instance of the same class
    ToyPrototype *clone()
    {
        return new Bike(*this);
    }
};

// Prototype Registry to manage prototypes
class PrototypeRegistry
{
private:
    unordered_map<int, ToyPrototype *> prototypeRegistry;

public:
    void initiatize()
    {
        prototypeRegistry[CAR] = new Car(1);
        prototypeRegistry[BIKE] = new Bike(2);
    }

    ToyPrototype *getProtoType(int type)
    {
        if (prototypeRegistry.find(type) != prototypeRegistry.end())
        {
            return prototypeRegistry[type]->clone();
        }
        return nullptr;
    }

    ~PrototypeRegistry()
    {
        cout << "[Destroy PrototypeRegistry] cleanup prototypeRegistry" << endl;

        for (auto proto : prototypeRegistry)
        {
            delete proto.second;
        }
        prototypeRegistry.clear();
    }
};

int main()
{
    PrototypeRegistry *pPototypeRegistry = new PrototypeRegistry();

    pPototypeRegistry->initiatize();

    ToyPrototype *pCarPrototype = pPototypeRegistry->getProtoType(CAR);
    ToyPrototype *pBikePrototype = pPototypeRegistry->getProtoType(BIKE);

    return 0;
}