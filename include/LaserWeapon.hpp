#ifndef LASERWEAPON_HPP_INCLUDED
#define LASERWEAPON_HPP_INCLUDED

#include "Weapon.hpp"

class LaserWeapon : public Weapon
{
public:
    LaserWeapon(Entity const& my_user);
    void fire();
    ~LaserWeapon();
};

#endif // LASERWEAPON_HPP_INCLUDED
