
#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "animal.h"

enum class AnimalType
{
    Cat,
    Dog,
};

class AnimalFactory
{
    public:
    AnimalFactory() {};
    ~AnimalFactory() {};
    Animal* create(AnimalType type)
    {
        Animal* animal = nullptr;
        switch (type)
        {
        case AnimalType::Cat:
        {
            animal = new AnimalCat();
        }break;
        case AnimalType::Dog:
        {
            animal = new AnimalDog();
        }break;
        default:
        {

        }break;
        }
        return animal;
    }
};

void factory_demo();

#endif
