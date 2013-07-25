#ifndef MISSILELAUNCHER_HPP_INCLUDED
#define MISSILELAUNCHER_HPP_INCLUDED

#include "Weapon.hpp"

class MissileLauncher : protected Weapon
{
public:
    void fire();
private:
};

#endif // MISSILELAUNCHER_HPP_INCLUDED
