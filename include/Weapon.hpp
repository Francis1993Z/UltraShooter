#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED


#include "Bullet.hpp"

#include "Entity.hpp"

class Weapon
{
public:
    virtual void fire();

protected:
    int damage;
    sf::Clock fire_intervale_clock;
    float fire_intervale;
    const Entity* user;
};
#endif // WEAPON_HPP_INCLUDED
