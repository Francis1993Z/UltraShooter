#ifndef ZOMBIE_HPP_INCLUDED
#define ZOMBIE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"

#include "Ennemy.hpp"

class Zombie : public Ennemy
{
public:

    Zombie(sf::Vector2f init_Position, Entity& init_Target, TEAM team);

    virtual unsigned int die() const;
    virtual void  update();


};

#endif // ZOMBIE_HPP_INCLUDED
