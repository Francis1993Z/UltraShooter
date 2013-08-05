#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "Projectile.hpp"
#include <iostream>


//! Les Bullet sont des projectiles de type POINT
/// Une fois cree, ils avancent dans une direction donnee

class Bullet : public Projectile
{

public:

    Bullet(sf::Vector2f myInitPosition, float myangle, TEAM team);
    Bullet(sf::Vector2f myInitPosition, float myangle, sf::Color myColor, int myDamage, float myvitesse, TEAM team);

    ~Bullet();

    virtual void UpdatePosition();

};

#endif // BULLET_HPP_INCLUDED
