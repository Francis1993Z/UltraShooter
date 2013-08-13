#include "Weapon.hpp"

using namespace std;
using namespace sf;

void Weapon::fire()
{

}

void Weapon::fire(sf::Vector2f target_position)
{

}

void Weapon::refresh()
{

}

void Weapon::update()
{

}

bool Weapon::isUpdatable() const
{
    return needRefresh;
}

Texture* Weapon::getSymbole(){

    return &symbole;
}

Weapon::~Weapon()
{

}
