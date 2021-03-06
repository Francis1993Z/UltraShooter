#ifndef MISSILELAUNCHER_HPP_INCLUDED
#define MISSILELAUNCHER_HPP_INCLUDED

#include "Weapon.hpp"

class Ennemy;

class MissileLauncher : public Weapon
{
public:
    MissileLauncher(Entity const& my_user, bool p_tirIllimity, unsigned int p_ammunitions, sf::Vector2f pos);
    void fire();
private:
    const Ennemy* my_target;
};

#endif // MISSILELAUNCHER_HPP_INCLUDED
