#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include "Projectile.hpp"
#include <iostream>


class Bullet : public sf::CircleShape, public Projectile
{

public:

    Bullet(sf::Vector2f myInitPosition, float myangle);
    Bullet(sf::Vector2f myInitPosition, float myangle, sf::Color myColor, int myDamage, float myvitesse);

    ~Bullet();

    virtual void UpdatePosition();

};

#endif // BULLET_HPP_INCLUDED
