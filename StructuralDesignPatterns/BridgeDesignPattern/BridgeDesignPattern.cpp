#include <iostream>
using namespace std;

// Implementor interface
class API
{
public:
    virtual void request(string data) = 0;
};

class HTTPAPI : public API
{
public:
    void request(string data)
    {
        cout << "HTTP API request : " << data << endl;
    }
};

class WebSocketAPI : public API
{
public:
    void request(string data)
    {
        cout << "WebSocket API request : " << data << endl;
    }
};

// Abstraction interface
class GUI
{
protected:
    API *pApi;

public:
    GUI(API *pApi) : pApi{pApi}
    {
    }

    virtual void sendData(string data) = 0;
};

class Button : public GUI
{
public:
    Button(API *pApi) : GUI{pApi}
    {
    }

    void sendData(string data)
    {
        cout << "Button sends data using ";
        pApi->request(data);
    }
};

class TextBox : public GUI
{
    public:
        TextBox(API *pApi) : GUI{pApi}
        {
    }

    void sendData(string data)
    {
        cout << "TextBox sends data using ";
        pApi->request(data);
    }
};


int main()
{
    API *pHttpApi = new HTTPAPI();

    GUI *pButtonGuiForHttp = new Button(pHttpApi);
    GUI *pTextBoxGuiForHttp = new TextBox(pHttpApi);

    pButtonGuiForHttp->sendData("Hello !!");
    pTextBoxGuiForHttp->sendData("Hello !!");

    API *pWebSocketApi = new WebSocketAPI();

    GUI *pButtonGuiForWebSoc = new Button(pWebSocketApi);
    GUI *pTextBoxGuiForWebSoc = new TextBox(pWebSocketApi);
    
    pButtonGuiForWebSoc->sendData("Hello !!");
    pTextBoxGuiForWebSoc->sendData("Hello !!");
}