#ifndef PROJECTILE_HPP_INCLUDED
#define PROJECTILE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>

class Projectile
{
public :

protected :
    int damage;
    float vitesse, angle;
    bool grow;
    sf::Vector2f myPosition;
};

#endif // PROJECTILE_HPP_INCLUDED
