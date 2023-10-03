#include <iostream>
#include "URLBuilder.hpp"
using namespace std;

class URLDirector
{
    URLBuilder *builder;

public:
    URLDirector(URLBuilder* builder) : builder{builder}
    {
    }

    void constructStandardURL()
    {
        builder->setHost("www.test.com");
        builder->setPort(":8080");
        builder->setPath("/path/to/resource");
    }

    void constructFullURL()
    {
        builder->setHost("www.test.com");
        builder->setPort(":8080");
        builder->setPath("/path/to/resource");
        builder->setQuery("?param1=val1&param2=val2");
    }
};