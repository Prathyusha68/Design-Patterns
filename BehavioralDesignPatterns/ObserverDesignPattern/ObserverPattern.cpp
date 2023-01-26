/**
 * Observer is a behavioral design pattern that lets you dene a subscription mechanism to notify multiple
 * objects about any events that happen to the object they’re observing.
 */
#include <iostream>
#include <list>
using namespace std;

/* Observers */
class ISubscriber
{
public:
    virtual void notify() = 0;
};

class Subscriber : public ISubscriber
{
    int subId;

public:
    Subscriber(int subId) : subId{subId}
    {
    }

    void notify()
    {
        cout << "Notifying..." << subId << endl;
    }
};

class ISubscriptionMgr
{
public:
    virtual void subscribe(Subscriber *sub) = 0;
    virtual void unSubscribe(Subscriber *sub) = 0;
    virtual void notify() = 0;
};

class SubscriptionMgr : public ISubscriptionMgr
{
    list<Subscriber *> subList;

public:
    ~SubscriptionMgr()
    {
        for (auto sub : subList)
        {
            delete sub;
        }
    }

    void subscribe(Subscriber *sub)
    {
        subList.push_back(sub);
    }

    void unSubscribe(Subscriber *sub)
    {
        subList.remove(sub);
    }

    void notify()
    {
        for (auto sub : subList)
        {
            sub->notify();
        }
    }
};

int main()
{
    Subscriber *sub1 = new Subscriber(1);
    Subscriber *sub2 = new Subscriber(2);

    SubscriptionMgr *subMgr = new SubscriptionMgr();
    subMgr->subscribe(sub1);
    subMgr->subscribe(sub2);
    subMgr->notify();
    cout << endl;

    subMgr->unSubscribe(sub2);
    subMgr->notify();
}