#ifndef PROJECTILE_HPP_INCLUDED
#define PROJECTILE_HPP_INCLUDED


#include "GlobalFunctions.h"



class Projectile
{
public :

    unsigned int getDamage() const;
 virtual void UpdatePosition();
 TEAM getmyTeam() const;
protected :

    sf::Vector2f myPosition;
    unsigned int damage;

    float vitesse, angle;
TEAM my_team;
    bool grow;
};

#endif // PROJECTILE_HPP_INCLUDED
