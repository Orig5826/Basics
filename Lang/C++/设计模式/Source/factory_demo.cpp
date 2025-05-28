
#include "factory.h"

void factory_demo(void) 
{
    AnimalCat* cat = AnimalFactory::create(AnimalType::Cat);
    cat->show();
    delete cat;

    AnimalCat* dog = AnimalFactory::create(AnimalType::Dog);
    dog->show();
    delete dog;
}
