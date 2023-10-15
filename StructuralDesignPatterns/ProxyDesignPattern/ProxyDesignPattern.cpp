#include <iostream>
using namespace std;

class WebPage
{
public:
    virtual void getContent(string url) = 0;
};

class WebPageImpl : public WebPage
{
public:
    void getContent(string url)
    {
        if (url == "www.youtube.com")
        {
            cout << "Welcome to Youtube !!" << endl;
        }
        else if (url == "www.google.com")
        {
            cout << "Welcom to Google !!" << endl;
        }
        else
        {
            cout << "Not Found - 404" << endl;
        }
    }
};

class ProxyWebPage : public WebPage
{
    WebPage *pWebPage;

public:
    ProxyWebPage()
    {
        pWebPage = new WebPageImpl();
    }

    void getContent(string url)
    {
        if ((url == "www.chatgpt.com") || (url == "www.openAi.com"))
        {
            cout << "Access Denied" << endl;
        }
        else
        {
            pWebPage->getContent(url);
        }
    }

    ~ProxyWebPage()
    {
        delete pWebPage;
    }
};

int main()
{
    ProxyWebPage* pProxyWebPage = new ProxyWebPage();
    pProxyWebPage->getContent("www.chatgpt.com");
    pProxyWebPage->getContent("www.youtube.com");
    pProxyWebPage->getContent("www.stackoverflow.com");

    return 0;
}