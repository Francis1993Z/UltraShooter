#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "GlobalFunctions.h"
#include "Entity.hpp"
#include "EntityWithWeapon.hpp"
#include "Hud.hpp"

class Player : public Entity, public EntityWithWeapon
{

    bool IamImmune;

    float rayon, ImmuneTime;

    unsigned long Score;

    bool firing;
    sf::FloatRect rect;
    sf::Clock weapon_clock;

    std::string PlayerName;

public:

    Player(sf::Vector2f init_position, TEAM team);

//!
/// stopMLAction(0 permet de réagire à des évènement.
/// Il peut être utile pour toute sorte d'actions.
    void stopMLAction();
    void update();
    unsigned long getScore();
    targetdata getTarget() const;
    void move_myhud(float vx, float vy);
    //void setSizeWindowHud(sf::Vector2f sizeWindow);
    void addPoints(int p);
    void modifierVie(int pv);
    void initHud();

    void Shoot();
    ~Player();

};

#endif // PLAYER_HPP_INCLUDED
