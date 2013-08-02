#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "Entity.hpp"
#include "Bullet.hpp"

class Weapon
{
public:
    virtual void fire();
    virtual void fire(sf::Vector2f target_position);
    virtual ~Weapon();
protected:
    int damage;
    sf::Clock fire_intervale_clock;
    float fire_intervale;
    const Entity* user;
};
#endif // WEAPON_HPP_INCLUDED
