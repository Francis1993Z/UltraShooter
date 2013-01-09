#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED


#include "PreHeader.h"
#include "Entity.hpp"

class Projectile : public Entity
{
public :

    bool CIO();
    sf::Shape GetProjectileSprite() const;
sf::Vector2f GetPosition() const;

protected :
    int vitesse, damage;
    bool grow;
    float vx,vy;
    sf::Vector2f ProjectilePosition;
    sf::Image ProjectileIMG;
    sf::Shape ProjectileSprite;

    unsigned int WinWidth,WinHeight;
};


#endif // PROJECTILE_H_INCLUDED
