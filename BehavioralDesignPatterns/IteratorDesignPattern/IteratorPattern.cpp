#include <iostream>
#include <list>

using namespace std;

/* Data */
class Product
{
    string prodName;
    int quantity = 0;

public:
    Product(string prodName, int quantity)
    {
        this->prodName = prodName;
        this->quantity = quantity;
    }

    string toString()
    {
        return ("Product Name : " + prodName + " #Quantity: " + to_string(quantity));
    }
};

/* Iterator */
template <class containerType>
class Iterator
{
    containerType *container;
    /**
     * Note: The variable declared with auto keyword should be initialized at the time of its declaration only
     * or else there will be a compile-time error. So, we can't use auto here.
     */
    list<Product>::iterator iter;

public:
    Iterator(containerType *cart)
    {
        container = cart;
        iter = cart->cartList.begin();
    }

    bool hasNext()
    {
        return (iter != container->cartList.end());
    }

    list<Product>::iterator next()
    {
        return iter++;
    }
};

/* Container */
class Cart
{
    list<Product> cartList;

public:
    friend class Iterator<Cart>;

    void addProduct(Product prod)
    {
        cartList.push_back(prod);
    }

    Iterator<Cart> *createIterator()
    {
        return new Iterator<Cart>(this);
    }
};

int main()
{
    Product prod1 = Product("LG Phone", 3);
    Product prod2 = Product("HP Laptop", 5);
    Product prod3("Bottle", 7), prod4("Cup", 8);
    Cart *cart = new Cart();

    cart->addProduct(prod1);
    cart->addProduct(prod2);
    cart->addProduct(prod3);
    cart->addProduct(prod4);

    Iterator<Cart> *iter = cart->createIterator();
    while (iter->hasNext())
    {
        cout << iter->next()->toString() << endl;
    }
}