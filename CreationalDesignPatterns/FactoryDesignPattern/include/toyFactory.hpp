#ifndef TOYFACTORY_HPP
#define TOYFACTORY_HPP
#include <iostream>
#include "toy.hpp"
#include "car.hpp"
#include "bike.hpp"

using namespace std;

class ToyFactory
{
public:
    static Toy *getToy(int type);
};
#endif