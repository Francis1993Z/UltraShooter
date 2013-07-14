#ifndef ZOMBIE_HPP_INCLUDED
#define ZOMBIE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"

#include "Ennemy.hpp"

class Zombie : public Ennemy, public sf::CircleShape
{
  public:
  Zombie();
  Zombie(sf::Vector2f init_Position, Player& init_Target);
void  Update();
unsigned int getDamage() const;
  private:
unsigned int damage;
};

#endif // ZOMBIE_HPP_INCLUDED
