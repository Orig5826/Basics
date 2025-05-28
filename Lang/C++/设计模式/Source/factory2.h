
#ifndef _FACTORY2_H_
#define _FACTORY2_H_

#include "animal.h"

class AnimalFactory2
{
    public:
    AnimalFactory2() {};
    ~AnimalFactory2() {};
    virtual Animal* create() = 0;
};

class CatFactory: public AnimalFactory2
{
    public:
    CatFactory() {};
    Animal* create()
    {
        return new AnimalCat();
    }
};

class DogFactory : public AnimalFactory2
{
    public:
    DogFactory() {};
    Animal* create()
    {
        return new AnimalDog();
    }
};

void factory2_demo();

#endif
