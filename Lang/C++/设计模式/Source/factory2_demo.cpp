
#include "factory2.h"

void factory2_demo()
{
    AnimalFactory2 *factory = new CatFactory();
    Animal *animal = factory->create();
    animal->show();
    delete animal;

    AnimalFactory2 *factory2 = new DogFactory();
    Animal *animal2 = factory2->create();
    animal2->show();
    delete animal2;
}
