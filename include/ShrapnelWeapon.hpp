#ifndef SHRAPNELWEAPON_HPP_INCLUDED
#define SHRAPNELWEAPON_HPP_INCLUDED

#include "Weapon.hpp"

class ShrapnelWeapon : public Weapon
{
public:
    ShrapnelWeapon(sf::Shape const& my_user);
    void fire();
};

#endif // SHRAPNELWEAPON_HPP_INCLUDED
