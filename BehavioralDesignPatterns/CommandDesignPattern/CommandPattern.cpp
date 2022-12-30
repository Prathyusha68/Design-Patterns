#include <iostream>
using namespace std;

/* Command Interface */
class Command
{
public:
    virtual void execute() = 0;
};

/* Receivers */
class Light
{
public:
    void lightOn()
    {
        cout << "Light is ON" << endl;
    }
    void lightOff()
    {
        cout << "Light is OFF" << endl;
    }
};

class LightOnCommand : public Command
{
    Light *light = nullptr;

public:
    ~LightOnCommand()
    {
        if (light)
            delete light;
    }

    LightOnCommand(Light *Light) : light{light}
    {
    }

    void execute()
    {
        light->lightOn();
    }
};

class LightOffCommand : public Command
{
    Light *light = nullptr;

public:
    ~LightOffCommand()
    {
        if (light)
            delete light;
    }

    LightOffCommand(Light *light) : light{light}
    {
    }

    void execute()
    {
        light->lightOff();
    }
};

class TV
{
    int volume = 0;

public:
    void tvOn()
    {
        cout << "TV is ON" << endl;
    }

    void setDeafultVolume()
    {
        this->volume = 7;
        cout << "setting deafult volume : " << volume << endl;
    }

    void tvOff()
    {
        cout << "TV is OFF" << endl;
    }
};

class TVOnCommand : public Command
{
    TV *tv = nullptr;

public:
    ~TVOnCommand()
    {
        if (tv)
            delete tv;
    }

    TVOnCommand(TV *tv) : tv{tv}
    {
    }

    void execute()
    {
        tv->tvOn();
        tv->setDeafultVolume();
    }
};

class TVOffCommand : public Command
{
    TV *tv = nullptr;

public:
    ~TVOffCommand()
    {
        if (tv)
        {
            delete tv;
        }
    }

    TVOffCommand(TV *tv) : tv{tv}
    {
    }

    void execute()
    {
        tv->tvOff();
    }
};

/* Invoker */
class RemoteController
{
    Command *cmd = nullptr;

public:
    ~RemoteController()
    {
        if (cmd)
            delete cmd;
    }
    void setCommand(Command *cmd)
    {
        this->cmd = std::move(cmd);
    }

    void executeCommand()
    {
        cmd->execute();
    }
};

int main()
{
    Light *light = new Light();
    TV *tv = new TV();
    RemoteController *remote = new RemoteController();

    remote->setCommand(new LightOnCommand(light));
    remote->executeCommand();

    remote->setCommand(new LightOffCommand(light));
    remote->executeCommand();

    remote->setCommand(new TVOnCommand(tv));
    remote->executeCommand();

    remote->setCommand(new TVOffCommand(tv));
    remote->executeCommand();
}