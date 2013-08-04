#ifndef LASERWEAPON_HPP_INCLUDED
#define LASERWEAPON_HPP_INCLUDED

#include "Weapon.hpp"
#include "LaserBeam.hpp"

class LaserWeapon : public Weapon
{
Laserbeam* my_laserbeam;
public:
    LaserWeapon(Entity const& my_user);
    void fire();
    void refresh();
    void stopLaserBeam();
    ~LaserWeapon();
};

#endif // LASERWEAPON_HPP_INCLUDED
