#ifndef SOLOGAME_HPP_INCLUDED
#define SOLOGAME_HPP_INCLUDED

#include "Game.hpp"

class SoloGame : public Game
{
public:
SoloGame();
void updateGame();
 void updateEntity();
 void updatePhysics();
 void upgradePhase();
 void EndGame();
 void Pause();
 void drawgame(sf::RenderWindow& target);
~SoloGame();
};


#endif // SOLOGAME_HPP_INCLUDED
