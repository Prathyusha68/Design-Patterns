#include <iostream>
#include "../include/toy.hpp"
#include "../include/car.hpp"
#include "../include/bike.hpp"
#include "../include/toyFactory.hpp"

using namespace std;

Toy *ToyFactory ::getToy(int type)
{
    Toy *toy = NULL;
    switch (type)
    {
    case 1:
        toy = new Bike();
        break;
    case 2:
        toy = new Car();
        break;
    default:
        cout << "Invalid toy type please re-enter type :" << endl;
        toy = NULL;
        break;
    }
    return toy;
}