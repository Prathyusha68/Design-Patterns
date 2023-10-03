#ifndef URL_HPP
#define URL_HPP
#include <iostream>
#include "URL.cpp"
using namespace std;

class URLBuilder
{
public:
    virtual void setHost(string host) = 0;

    virtual void setPort(string port) = 0;

    virtual void setPath(string path) = 0;

    virtual void setQuery(string query) = 0;

    virtual URL getURL() = 0;
};
#endif