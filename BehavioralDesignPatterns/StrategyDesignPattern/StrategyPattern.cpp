/**
 * Strategy is a behavioral design pattern that lets you define a family of algorithms, put each of them into a
 * separate class, and make their objects interchangeable.
 **/
#include <iostream>
#include <bits/stdc++.h>
#include <memory>
using namespace std;

class Strategy
{
public:
    virtual string executeAlgo(string str) = 0;
};

class ConcreteClassStrategyA : public Strategy
{
public:
    string executeAlgo(string str)
    {
        std::sort(std::begin(str), std::end(str));
        return str;
    }
};

class ConcreateClassStartegyB : public Strategy
{
public:
    string executeAlgo(string str)
    {
        std::sort(std::begin(str), std::end(str), greater<>());
        return str;
    }
};
class Context
{
    unique_ptr<Strategy> startegy;

public:
    Context(unique_ptr<Strategy> &&strategy) : startegy{std::move(strategy)}
    {
    }

    /* optional - if required to change after object creation */
    void setStrategy(unique_ptr<Strategy> &&strategy)
    {
        this->startegy = std::move(strategy);
    }

    void execute(string str)
    {
        str = startegy->executeAlgo(str);

        cout << "String with provided strategy :" << str.c_str() << endl;
    }
};

int main()
{
    unique_ptr<Context> ctxt = make_unique<Context>(make_unique<ConcreteClassStrategyA>());
    ctxt->execute("ebacdf");

    unique_ptr<Context> ctxt1 = make_unique<Context>(make_unique<ConcreateClassStartegyB>());
    ctxt1->execute("ebacdf");
}