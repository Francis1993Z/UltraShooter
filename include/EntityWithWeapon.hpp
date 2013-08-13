#ifndef ENTITYWITHWEAPON_HPP_INCLUDED
#define ENTITYWITHWEAPON_HPP_INCLUDED

#include <vector>

#include "Weapon.hpp"
#include "AutomaticWeapon.hpp"
#include "ShrapnelWeapon.hpp"
#include "LaserWeapon.hpp"

class EntityWithWeapon
{
protected:
    std::vector<Weapon *> my_weapon;
    int actual_weapon;
public:
    void change_Weapon(int delta);
    sf::Texture* getSymboleActualWeapon();
    bool isTirIllimity() const;
    unsigned int getAmmunitions() const;
    virtual ~EntityWithWeapon();
};

#endif // ENTITYWITHWEAPON_HPP_INCLUDED
