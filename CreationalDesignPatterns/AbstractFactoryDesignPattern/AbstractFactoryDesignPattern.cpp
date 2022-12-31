#include <iostream>
using namespace std;

/* Button - windows button and Mac button */
class IButton
{
public:
    virtual void click() = 0;
};

class WinButton : public IButton
{
public:
    void click()
    {
        cout << "Windows OS : clicked button " << endl;
    }
};

class MacButton : public IButton
{
public:
    void click()
    {
        cout << "Mac OS : clicked box " << endl;
    }
};

/* Check Box - Windows check box and Mac check box */
class ICheckBox
{
public:
    virtual void check() = 0;
};

class WinCheckBox : public ICheckBox
{
public:
    void check()
    {
        cout << "Windows OS : checked box " << endl;
    }
};

class MacCheckBox : public ICheckBox
{
public:
    void check()
    {
        cout << "Mac OS : checked box " << endl;
    }
};

/* Factory Interface - WIN factory and MAC factory */
class IFactory
{
public:
    virtual IButton *createButton() = 0;
    virtual ICheckBox *createCheckBox() = 0;
};

class WinFactory : public IFactory
{
public:
    IButton *createButton()
    {
        return new WinButton();
    }
    ICheckBox *createCheckBox()
    {
        return new WinCheckBox();
    }
};

class MacFactory : public IFactory
{
public:
    IButton *createButton()
    {
        return new MacButton();
    }

    ICheckBox *createCheckBox()
    {
        return new MacCheckBox();
    }
};

/* GUI Abstract Factory Interface */
class GUIAbstractFactory
{

public:
    static IFactory *createFactory(int osType)
    {
        IFactory *fact = NULL;
        if (osType == 1)
        {
            return new WinFactory();
        }
        else if (osType == 2)
        {
            return new MacFactory();
        }
        else
        {
            return NULL;
        }
    }
};

int main()
{
    while (1)
    {
        int osType = 0;
        cout << "Enter OS Type (1 -> WIN 2 -> MAC) or zero to exit: " << endl;
        cin >> osType;

        if (!osType)
            break;

        IFactory *fact = GUIAbstractFactory::createFactory(osType);

        if (fact == NULL)
        {
            cout << "Invalid OS Type ..re-enter it" << endl;
            continue;
        }

        IButton *button = fact->createButton();
        button->click();

        ICheckBox *checkBox = fact->createCheckBox();
        checkBox->check();
    }
    cout << "Exit.." << endl;
}