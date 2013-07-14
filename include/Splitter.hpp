#ifndef SPLITTER_HPP_INCLUDED
#define SPLITTER_HPP_INCLUDED

#include "Zombie.hpp"

class Splitter : public Zombie
{
public:
    Splitter(sf::Vector2f init_Position, Player& init_Target, unsigned int level);
    unsigned int getNextLevel() const;
private:
unsigned int my_level;
};

#endif // SPLITTER_HPP_INCLUDED
