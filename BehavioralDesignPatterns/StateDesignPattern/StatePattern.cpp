#include <iostream>
#include <memory>

using namespace std;

class Context
{
    class State *state = nullptr;

public:
    Context(State *state);

    ~Context();

    State *getState();

    void setState(State *state);

    void execute();
};

class State
{
public:
    virtual void handle(Context *) = 0;
};

class LightOnState : public State
{
public:
    void handle(Context *ctxt);
};

class LightOffState : public State
{
public:
    void handle(Context *ctxt)
    {
        cout << "Light is OFF" << endl;
        ctxt->setState(new LightOnState());
    }
};

Context::Context(State *state) : state{state}
{
}

Context::~Context()
{
    if (state)
    {
        delete state;
        state = nullptr;
    }
}

State *Context::getState()
{
    return state;
}

void Context::setState(State *state)
{
    if (state)
    {
        delete this->state;
        this->state = nullptr;
    }
    this->state = std::move(state);
}

void Context::execute()
{
    state->handle(this);
}

void LightOnState::handle(Context *ctxt)
{
    cout << "Light is ON" << endl;
    ctxt->setState(new LightOffState());
}

int main()
{
    unique_ptr<Context> ctxt = make_unique<Context>(new LightOnState());
    ctxt->execute();
    ctxt->execute();
    ctxt->execute();
    ctxt->execute();
}