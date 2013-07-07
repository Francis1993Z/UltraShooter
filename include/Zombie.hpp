#ifndef ZOMBIE_HPP_INCLUDED
#define ZOMBIE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"

#include "Ennemy.hpp"

class Zombie : public Ennemy, public sf::CircleShape
{
  public:
  Zombie(sf::Vector2f init_Position, Player& init_Target);
void  Update();
  private:
int damage;
};

#endif // ZOMBIE_HPP_INCLUDED