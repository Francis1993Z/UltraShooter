#ifndef SPLITTER_HPP_INCLUDED
#define SPLITTER_HPP_INCLUDED

#include "Zombie.hpp"

class Splitter : public Zombie
{
public:

    Splitter(sf::Vector2f init_Position, Entity& init_Target, unsigned int level, TEAM team);
    virtual unsigned int die() const;
    unsigned int getNextLevel() const;
    unsigned int getLevel() const;
private:
    unsigned int my_level;
};

#endif // SPLITTER_HPP_INCLUDED
