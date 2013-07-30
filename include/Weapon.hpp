#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include <SFML/Graphics/Shape.hpp>
#include "Bullet.hpp"

class Weapon
{
public:
    virtual void fire();
    virtual ~Weapon();
protected:
    int damage;
    sf::Clock fire_intervale_clock;
    float fire_intervale;
    const sf::Shape* user;
};
#endif // WEAPON_HPP_INCLUDED
