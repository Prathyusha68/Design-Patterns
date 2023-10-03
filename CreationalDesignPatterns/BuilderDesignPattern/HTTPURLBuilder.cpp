#include <iostream>
#include "URLBuilder.hpp"

using namespace std;

class HTTPURLBuilder : public URLBuilder
{
    URL url;

public:
    HTTPURLBuilder()
    {
        url.setScheme("http");
    }

    void setHost(string host)
    {
        url.setHost(host);
    }

    void setPort(string port)
    {
        url.setPort(port);
    }

    void setPath(string path)
    {
        url.setPath(path);
    }

    void setQuery(string query)
    {
        url.setQuery(query);
    }

    URL getURL()
    {
        return url;
    }
};