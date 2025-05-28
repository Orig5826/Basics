
#include "factory.h"

void factory_demo()
{
    AnimalFactory factory;
    AnimalCat* cat = static_cast<AnimalCat*>(factory.create(AnimalType::Cat));
    if (cat) {
        cat->show();
        delete cat;
    }

    AnimalDog* dog = static_cast<AnimalDog*>(factory.create(AnimalType::Dog));
    if (dog) {
        dog->show();
        delete dog;
    }
}