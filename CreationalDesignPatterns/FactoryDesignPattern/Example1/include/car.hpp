#ifndef CAR_HPP
#define CAR_HPP

#include <iostream>
#include "toy.hpp"
using namespace std;

class Car : public Toy
{
public:
    void createToy();
};
#endif