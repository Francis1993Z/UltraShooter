#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Entity : public sf::Shape
{
public:
    Entity& getAdresse();
private:
};

#endif // ENTITY_HPP_INCLUDED
