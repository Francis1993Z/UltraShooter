#ifndef MISSILELAUNCHER_HPP_INCLUDED
#define MISSILELAUNCHER_HPP_INCLUDED

#include "Weapon.hpp"

class Ennemy;

class MissileLauncher : public Weapon
{
public:
    MissileLauncher(sf::Shape const& my_user);
    void fire();
private:
    const Ennemy* my_target;
};

#endif // MISSILELAUNCHER_HPP_INCLUDED
