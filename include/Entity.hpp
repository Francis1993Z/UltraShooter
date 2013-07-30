#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Entity : public sf::RectangleShape
{
protected:
    long vie;
    Entity(long c) : vie(c) { }
public:
    sf::FloatRect getCollisionBox();
    void subirDegats(unsigned int p_damage);
    virtual void modifierVie(int pv);
    bool alive() const;

};

#endif // ENTITY_HPP_INCLUDED
