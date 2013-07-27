#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"
#include "Hud.hpp"


#include "EntityWithWeapon.hpp"


class Player : public sf::CircleShape, public EntityWithWeapon
{

    bool IamImmune;

    float rayon, ImmuneTime;
    static const float vitesse;

    unsigned short Life;
    unsigned long Score;

    Hud hud;

    sf::FloatRect rect;
    sf::Clock weapon_clock;

    //sf::RenderWindow myWindow;

    std::string PlayerName;

public:

    Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f tailleFenetre);
    //void SetRenderWindow(sf::RenderWindow &mynewWindow);

    sf::FloatRect getCollisionBox();

    sf::Vector2i GetWindowPosition(sf::RenderWindow &theRenderWindow) const;

    sf::Text getLifeHud();
    sf::Text getScoreHud();

    void move_myhud(float vx, float vy);
    void setSizeWindowHud(sf::Vector2f sizeWindow);
    void addPoints(int p);
    void subirDegats(unsigned int p_damage);
    void modifierVie(int pv);


    float getRayon();
    float getVitesse() const;
    void Shoot();

    bool ReadyToShoot() const;
    bool alive() const;

    ~Player();

};

#endif // PLAYER_HPP_INCLUDED
