#ifndef EXPLOSIVE_HPP_INCLUDED
#define EXPLOSIVE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Projectile.hpp"

class Explosive : public sf::RectangleShape, public Projectile
{

public:

   virtual void UpdatePosition();

};

#endif // EXPLOSIVE_HPP_INCLUDED
