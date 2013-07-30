#include "Entity.hpp"
#include <iostream>

using namespace std;
using namespace sf;

void Entity::subirDegats(unsigned int p_damage)
{
    modifierVie(-p_damage);
}

bool Entity::alive() const
{
    if (vie > 0) return true;
    return false;
}

void Entity::modifierVie(int pv)
{
    vie+=pv;
}

sf::FloatRect Entity::getCollisionBox()
{
    return getGlobalBounds();
}
