#include <iostream>
#include <vector>

using namespace std;

class Book;
class Fruit;

class Visitor
{
public:
    virtual int visit(Book *apBook) = 0;
    virtual int visit(Fruit *apFruit) = 0;
};

class ItemElement
{
public:
    virtual int accept(Visitor *apShoppingCartVisitor) = 0;
};

class Book : public ItemElement
{
    int cost;

public:
    Book(int cost) : cost{cost}
    {
    }

    int getCost()
    {
        return cost;
    }

    int accept(Visitor *apShoppingCartVisitor)
    {
        return apShoppingCartVisitor->visit(this);
    }
};

class Fruit : public ItemElement
{
    int costPerKg;
    int weight;

public:
    Fruit(int costPerKg, int weight) : costPerKg{costPerKg}, weight{weight}
    {
    }

    int getCostPerKg()
    {
        return costPerKg;
    }

    int getWeight()
    {
        return weight;
    }

    int accept(Visitor *apShoppingCartVisitor)
    {
        return apShoppingCartVisitor->visit(this);
    }
};

class ShoppingCartVisitor : public Visitor
{
public:
    int visit(Book *apBook)
    {
        // Discount of 5Rs
        if (apBook->getCost() > 50)
            return apBook->getCost() - 5;

        return apBook->getCost();
    }

    int visit(Fruit *apFruit)
    {
        return (apFruit->getCostPerKg() * apFruit->getWeight());
    }
};

int main()
{
    vector<ItemElement *> vec;

    vec.push_back(new Book(100));
    vec.push_back(new Book(500));
    vec.push_back(new Book(30));

    vec.push_back(new Fruit(20, 5));
    vec.push_back(new Fruit(40, 2));
    vec.push_back(new Fruit(2, 5));

    int totalAmount = 0;
    Visitor *pShoppingCart = new ShoppingCartVisitor();

    for (auto it : vec)
    {
        totalAmount += it->accept(pShoppingCart);
    }

    cout << "Total Amount : " << totalAmount << endl;

    return 0;
}