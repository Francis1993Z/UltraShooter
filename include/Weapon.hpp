#ifndef WEAPON_HPP_INCLUDED
#define WEAPON_HPP_INCLUDED

#include "SFML/System.hpp"
#include "Bullet.hpp"


class Player;

class Weapon
{
public:
    virtual void fire();
protected:
    int damage;
Player* user;
};
#endif // WEAPON_HPP_INCLUDED
