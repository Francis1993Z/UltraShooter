#ifndef AUTOMATICWEAPON_HPP_INCLUDED
#define AUTOMATICWEAPON_HPP_INCLUDED

#include "Weapon.hpp"

class AutomaticWeapon : public Weapon
{
public:
    AutomaticWeapon();
    void fire(sf::Vector2f TargetPosition, sf::Vector2f player_pos);
private:
    sf::Clock fire_intervale;
};

#endif // AUTOMATICWEAPON_HPP_INCLUDED
