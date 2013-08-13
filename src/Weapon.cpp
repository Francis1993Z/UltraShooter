#include "Weapon.hpp"

using namespace std;
using namespace sf;

Weapon::Weapon(bool p_tirIllimity, unsigned int p_ammunitions){

    tirIllimity = p_tirIllimity;
    ammunitions = p_ammunitions;
}

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

bool Weapon::isTirIllimity() const{

 return tirIllimity;
}

unsigned int Weapon::getAmmunitions() const{

    return ammunitions;
}

Weapon::~Weapon()
{

}
