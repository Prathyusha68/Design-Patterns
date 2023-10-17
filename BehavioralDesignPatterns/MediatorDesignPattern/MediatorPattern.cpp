#include <iostream>
#include <list>
using namespace std;

class User;

class ChatMediator
{
public:
    virtual void sendRequest(User *pRequestingUser, string msg) = 0;
    virtual void addUsers(User *pRequestingUser) = 0;
};

class User
{
public:
    virtual void sendRequest(string msg) = 0;
    virtual void receiveMsg(string msg) = 0;
};

class UserConcrete : public User
{
    ChatMediator *pChatMediator;

public:
    UserConcrete(ChatMediator *pChatMediator) : pChatMediator{pChatMediator}
    {
    }

    void sendRequest(string msg)
    {
        pChatMediator->sendRequest(this, msg);
    }

    void receiveMsg(string msg)
    {
        cout << "Message received is : " << msg << endl;
    }
};

class ChatRoom : public ChatMediator
{
    list<User *> userList;

public:
    void sendRequest(User *pRequestingUser, string msg)
    {
        for (auto itr : userList)
        {
            if (itr != pRequestingUser)
            {
                itr->receiveMsg(msg);
            }
        }
    }

    void addUsers(User *pRequestingUser)
    {
        userList.push_back(pRequestingUser);
    }
};

int main()
{
    ChatMediator *pChatMediator = new ChatRoom();

    User *pUser1 = new UserConcrete(pChatMediator);
    User *pUser2 = new UserConcrete(pChatMediator);

    pChatMediator->addUsers(pUser1);
    pChatMediator->addUsers(pUser2);

    pUser1->sendRequest("Hi to all Users!! from User 1");
    pUser1->sendRequest("Hi to all Users!! from User 2");

    return 0;
}