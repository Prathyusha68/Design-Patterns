/**
 * The Flyweight pattern is a structural design pattern that aims to minimize memory usage or computational expenses
 * by sharing as much as possible with related objects. It's particularly useful when there are a large number of
 * similar objects that could be consolidated to save resources.
 **/
#include <iostream>
#include <unordered_map>
using namespace std;

enum
{
    CIRCLE,
    RECTANGLE
};

// Flyweight interface
class Shape
{
public:
    virtual void draw(int x, int y) = 0;
};

// Concrete Flyweight: Circle
class Circle : public Shape
{
    // Intrinsic state shared among objects
    string color;
    int radius;

public:
    Circle(string color, int radius) : color{color}, radius{radius}
    {
        cout << "Circle constructor !!!" << endl;
    }

    // Extrinsic state
    void draw(int x, int y)
    {
        cout << "Drawing a circle with color : " << color.c_str() << " radius : " << radius;
        cout << " at position (x,y) : (" << x << "," << y << ")" << endl;
    }
};

// Concrete Flyweight: Rectangle
class Rectangle : public Shape
{
    // Intrinsic state shared among objects
    string color;
    int length, breadth;

public:
    Rectangle(string color, int length, int breadth) : color{color}, length{length}, breadth{breadth}
    {
        cout << "Rectangle constructor !!!" << endl;
    }

    // Extrinsic state
    void draw(int x, int y)
    {
        cout << "Drawing a rectangle with color : " << color.c_str() << " length : " << length << " breadth : " << breadth;
        cout << " at position (x,y) : (" << x << "," << y << ")" << endl;
    }
};

// Flyweight Factory
class ShapeFactory
{
    unordered_map<int, Shape *> shapes;

public:
    Shape *getShape(int key)
    {
        if (shapes.find(key) != shapes.end())
        {
            return shapes[key];
        }
        else
        {
            if (key == CIRCLE)
            {
                shapes[key] = new Circle("Red", 10);
                return shapes[key];
            }
            else if (key == RECTANGLE)
            {
                shapes[key] = new Rectangle("Blue", 10, 20);
                return shapes[key];
            }
        }

        return NULL;
    }

    ~ShapeFactory()
    {
        for (auto shape : shapes)
        {
            delete shape.second;
        }

        shapes.clear();
    }
};

int main()
{
    ShapeFactory shapeFactory;

    // Both pCircle1 and pCircle2 will point to the same Circle object due to Flyweight pattern
    Shape *pCircle1 = shapeFactory.getShape(CIRCLE);
    pCircle1->draw(4, 5);

    Shape *pCircle2 = shapeFactory.getShape(CIRCLE);
    pCircle2->draw(3, 2);

    // Both pRectangle1 and pRectangle2 will point to the same Rectangle object due to Flyweight pattern
    Shape *pRectangle1 = shapeFactory.getShape(RECTANGLE);
    pRectangle1->draw(5, 7);

    Shape *pRectangle2 = shapeFactory.getShape(RECTANGLE);
    pRectangle2->draw(9, 8);

    return 0;
}