
#include "factory3.h"

void factory3_demo(void)
{
    AnimalHomeFactory *home = new CatHomeFactory();
    AnimalHome* cathome = home->create(new AnimalCat(), new ModernHouse());
    if(cathome)
    {
        cathome->show();
        delete cathome;
    }

    AnimalHomeFactory *home2 = new DogHomeFactory();
    AnimalHome* doghome = home2->create(new AnimalDog(), new SimpleHouse());
    if(doghome)
    {
        doghome->show();
        delete doghome;
    }

    delete home;
    delete home2;
}
