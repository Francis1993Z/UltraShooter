#ifndef AUTOMATICWEAPON_HPP_INCLUDED
#define AUTOMATICWEAPON_HPP_INCLUDED

#include "Weapon.hpp"


class AutomaticWeapon : public Weapon
{
public:
    AutomaticWeapon(Entity const& my_user);
    void fire();
    void fire(sf::Vector2f target_position);
};

#endif // AUTOMATICWEAPON_HPP_INCLUDED
