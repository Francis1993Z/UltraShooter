#ifndef RAIDER_HPP_INCLUDED
#define RAIDER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"

#include "Ennemy.hpp"
#include "EntityWithWeapon.hpp"

class Raider: public Ennemy, public EntityWithWeapon
{
public:
    Raider(sf::Vector2f init_Position, Entity& init_Target, TEAM team);

    virtual unsigned int die() const;
    virtual void  update();
};

#endif // RAIDER_HPP_INCLUDED
