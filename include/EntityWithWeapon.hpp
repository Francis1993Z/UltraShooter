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
 //EntityWithWeapon(sf::Transformable const& my_Entity);
 //sf::Transformable getEntity() const;
    void change_Weapon(int delta);
//const sf::Transformable* entity;
};

#endif // ENTITYWITHWEAPON_HPP_INCLUDED
