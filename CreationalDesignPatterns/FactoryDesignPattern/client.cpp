/* How to run this :
 *    g++ -c .\src\*
 *    g++ -c .\client.cpp
 *    g++ -o factory .\bike.o .\car.o .\toy.o .\toyFactory.o .\client.o
 *    .\factory.exe
 */

#include <iostream>
#include "include/toyFactory.hpp"

using namespace std;

int main()
{
    while (1)
    {
        int toyType = 0;
        cout << "Enter type of toy or zero to exit" << endl;
        cin >> toyType;

        if (!toyType)
            break;

        Toy *toy = ToyFactory::getToy(toyType);
        if (toy)
        {
            toy->createToy();
            delete toy;
        }
    }
    cout << "Exit.." << endl;
}