#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"
#include "Hud.hpp"

class Player : public sf::CircleShape
{
public:
    Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f tailleFenetre);
    //void SetRenderWindow(sf::RenderWindow &mynewWindow);
    float Shoot(sf::Vector2f TargetPosition, sf::RenderWindow &myRenderWindow);
    sf::Vector2i GetWindowPosition(sf::RenderWindow &theRenderWindow) const;
    sf::Text getLifeHud();
    sf::Text getScoreHud();
    void move_myhud(float vx, float vy);
    float getRayon();
    float getVitesse() const;
    sf::FloatRect getCollisionBox();
    void setSizeWindowHud(sf::Vector2f sizeWindow);
    void addPoints(int p);
    ~Player();

private:

    bool IamImmune;
    float rayon, ImmuneTime;
    //Immunity Timer
    unsigned long Score;
    unsigned short Life;
    const float vitesse = 15.0f;
    sf::FloatRect rect;
    Hud hud;
    //sf::RenderWindow myWindow;

    std::string PlayerName;
};

#endif // PLAYER_HPP_INCLUDED
