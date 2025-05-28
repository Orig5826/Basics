#include "factory.h"

void* AnimalFactory::create(AnimalType type)
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