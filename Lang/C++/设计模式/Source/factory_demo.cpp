
#include "factory.h"

void factory_demo()
{
    AnimalFactory* factory = new AnimalFactory();
    AnimalCat* cat = dynamic_cast<AnimalCat*>(factory->create(AnimalType::Cat));
    if (cat) {
        cat->show();
        delete cat;
    }

    AnimalDog* dog = dynamic_cast<AnimalDog*>(factory->create(AnimalType::Dog));
    if (dog) {
        dog->show();
        delete dog;
    }

    delete factory;
}
