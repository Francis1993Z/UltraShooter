#ifndef PROJECTILE_HPP_INCLUDED
#define PROJECTILE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>

#include "GlobalFunctions.h"

class Projectile : public sf::RectangleShape
{
public :
    collisiontype getCollisionType() const;
    unsigned int getDamage() const;
    virtual void UpdatePosition();
    virtual void setI(sf::Vector2f new_I);
    virtual sf::Vector2f getI() const;
    TEAM getTeam() const;
    virtual ~Projectile();
protected :

    sf::Vector2f myPosition;
    unsigned int damage;
    sf::Vector2f I;//point d'impact
    float vitesse, angle;
    TEAM my_team;
    collisiontype my_collisiontype;
};

#endif // PROJECTILE_HPP_INCLUDED
