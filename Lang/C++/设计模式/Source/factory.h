
#ifndef _FACTORY_
#define _FACTORY_

#include <iostream>
using namespace std;

enum class AnimalType
{
    Cat,
    Dog,
};

class Animal
{
    public:
    virtual ~Animal() = default;
    void show() { cout << "I am an animal" << endl; };
};

class AnimalCat : public Animal
{
    public:
    AnimalCat()
    {
        std::cout << "AnimalCat constructor" << std::endl;
    };
    ~AnimalCat() {};
    void show() { cout << "I am a cat" << endl; }
};

class AnimalDog : public Animal
{
    public:
    AnimalDog()
    {
        std::cout << "AnimalDog constructor" << std::endl;
    };
    ~AnimalDog() {};
    void show() { cout << "I am a dog" << endl; }
};

class AnimalFactory
{
    public:
    AnimalFactory() {};
    ~AnimalFactory() {};
    void* create(AnimalType);
};

void factory_demo();

#endif
