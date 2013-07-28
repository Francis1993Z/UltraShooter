#ifndef ENTITYWITHWEAPON_HPP_INCLUDED
#define ENTITYWITHWEAPON_HPP_INCLUDED

#include "Weapon.hpp"
#include "AutomaticWeapon.hpp"
#include "ShrapnelWeapon.hpp"
#include <vector>


class EntityWithWeapon
{
protected:
  std::vector<Weapon *> my_weapon;
     int actual_weapon;
public:
    void change_Weapon(int delta);
};

#endif // ENTITYWITHWEAPON_HPP_INCLUDED
