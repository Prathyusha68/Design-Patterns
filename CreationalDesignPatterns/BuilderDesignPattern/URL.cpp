#include <iostream>
#include <string>

using namespace std;

class URL
{
    string scheme;
    string host;
    string port;
    string path;
    string query;

public:
    void setScheme(string scheme)
    {
        this->scheme = scheme;
    }

    void setHost(string host)
    {
        this->host = host;
    }

    void setPort(string port)
    {
        this->port = port;
    }

    void setPath(string path)
    {
        this->path = path;
    }

    void setQuery(string query)
    {
        this->query = query;
    }

    void printURL()
    {
        cout << scheme << "://" << host << port << path;

        if(!query.empty())
        {
            cout << query;
        }
        cout << endl;
    }
};