#ifndef PROJECTILE_HPP_INCLUDED
#define PROJECTILE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>

class Projectile
{
public :

    unsigned int getDamage() const;

protected :

    sf::Vector2f myPosition;
    unsigned int damage;

    float vitesse, angle;

    bool grow;
};

#endif // PROJECTILE_HPP_INCLUDED
