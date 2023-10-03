#include<iostream>
#include "URLBuilder.hpp"
#include "HTTPURLBuilder.cpp"
#include "URLDirector.cpp"

using namespace std;

int main()
{
    URLBuilder *pHttpBuilder = new HTTPURLBuilder();
    URLDirector *pURLDirector = new URLDirector(pHttpBuilder);

    pURLDirector->constructStandardURL();
    URL standardURL = pHttpBuilder->getURL();
    standardURL.printURL();

    pURLDirector->constructFullURL();
    URL fullURL = pHttpBuilder->getURL();
    fullURL.printURL();

    return 0;
}