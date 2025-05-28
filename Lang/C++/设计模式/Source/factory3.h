
#ifndef _FACTORY3_H_
#define _FACTORY3_H_

#include "animal.h"
#include "house.h"

class AnimalHome
{
    private:
    Animal* m_animal;
    House* m_house;
    public:
    AnimalHome(Animal* animal, House* house) : m_animal(animal), m_house(house)
    {
    };
    ~AnimalHome()
    {
        if (m_animal != nullptr)
        {
            delete m_animal;
        }
        if (m_house != nullptr)
        {
            delete m_house;
        }
    };
    void show()
    {
        cout << "----- home -----" << endl;
        m_animal->show();
        m_house->show();
        cout << "----- ----- -----" << endl;
    };
};

class AnimalHomeFactory
{
    public:
    virtual AnimalHome* create(Animal* animal, House* house) = 0;
    virtual ~AnimalHomeFactory() = default;
};

class CatHomeFactory : public AnimalHomeFactory
{
    public:
    AnimalHome* create(Animal* animal, House* house)
    {
        return new AnimalHome(animal, house);
    };
};

class DogHomeFactory : public AnimalHomeFactory
{
    public:
    AnimalHome* create(Animal* animal, House* house)
    {
        return new AnimalHome(animal, house);
    }
};

void factory3_demo(void);

#endif
