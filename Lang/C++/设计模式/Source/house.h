
#ifndef _HOUSE_H_
#define _HOUSE_H_

#include <iostream>
using namespace std;

class House
{
    public:
    ~House() = default;
    virtual void show() = 0;
};

class SimpleHouse : public House
{
    public:
    SimpleHouse()
    {
        std::cout << "SimpleHouse constructor" << endl;
    };
    ~SimpleHouse() = default;
    void show() { cout << "simple house" << endl; };
};

class ModernHouse : public House
{
    public:
    ModernHouse()
    {
        std::cout << "ModernHouse constructor" << endl;
    };
    ~ModernHouse() = default;
    void show() { cout << "modern house" << endl; };
};

#endif
