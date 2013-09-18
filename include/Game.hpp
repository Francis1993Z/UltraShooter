#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Engine.hpp"
#include "Bonus.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
    std::list<Projectile *> ProjectilesArray;
    std::list<Entity *> EntityArray;
    std::list<Weapon *> WeaponArray;

    std::list<Obstacle> lObstacles;
    std::list<Bonus *> lBonus;

    std::vector<Map*> MapArray;

public:

    void addEnnemy(Ennemy* e);
    void addPlayer(Player* a);
    void addProjectile(Projectile* p);
    void rmProjectile(Projectile* p);

virtual void updateGame();
virtual void updateEntity();
virtual void updatePhysics();
virtual void upgradePhase();
virtual void EndGame();
virtual void Pause();
virtual void drawgame(sf::RenderWindow& target);

};

#endif // GAME_HPP_INCLUDED
