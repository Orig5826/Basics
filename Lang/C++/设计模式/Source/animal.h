
#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include <iostream>
using namespace std;

class Animal
{
    public:
    virtual ~Animal() = default;
    virtual void show() = 0;
};

class AnimalCat : public Animal
{
    public:
    AnimalCat()
    {
        std::cout << "AnimalCat constructor" << std::endl;
    };
    ~AnimalCat() {};
    void show() { cout << "cat" << endl; }
};

class AnimalDog : public Animal
{
    public:
    AnimalDog()
    {
        std::cout << "AnimalDog constructor" << std::endl;
    };
    ~AnimalDog() {};
    void show() { cout << "dog" << endl; }
};

#endif
