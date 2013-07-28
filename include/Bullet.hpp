#ifndef BULLET_HPP_INCLUDED
#define BULLET_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Projectile.hpp"


class Bullet : public sf::CircleShape, public Projectile
{

public:

    Bullet(sf::Vector2f myInitPosition, float myangle, TEAM y_TEAM);
    Bullet(sf::Vector2f myInitPosition, float myangle, sf::Color myColor, int myDamage, float myvitesse, TEAM y_TEAM);

    ~Bullet();

    virtual void UpdatePosition();

};

#endif // BULLET_HPP_INCLUDED
