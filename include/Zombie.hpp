#ifndef ZOMBIE_HPP_INCLUDED
#define ZOMBIE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"

#include "Ennemy.hpp"

class Zombie : public Ennemy
{
public:

    Zombie(sf::Vector2f init_Position, Player& init_Target);

    unsigned int die() const;
    void  update();


};

#endif // ZOMBIE_HPP_INCLUDED
