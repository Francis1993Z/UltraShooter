#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "GlobalFunctions.h"
#include "Hud.hpp"

#include "Entity.hpp"
#include "EntityWithWeapon.hpp"

class Player : public Entity, public EntityWithWeapon
{

    bool IamImmune;

    float rayon, ImmuneTime;

    unsigned long Score;

    Hud hud;
    bool firing;
    sf::FloatRect rect;
    sf::Clock weapon_clock;

    std::string PlayerName;

public:

    Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f tailleFenetre, TEAM team);

    sf::Text getLifeHud();
    sf::Text getScoreHud();

    void stopMLAction();

    unsigned long getScore();
    targetdata getTarget() const;
    void move_myhud(float vx, float vy);
    void setSizeWindowHud(sf::Vector2f sizeWindow);
    void addPoints(int p);
    float getRayon();
    void modifierVie(int pv);

    void Shoot();
    ~Player();

};

#endif // PLAYER_HPP_INCLUDED
