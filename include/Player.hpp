#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"
#include "Hud.h"

class Player : public sf::CircleShape
{
public:
    Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f tailleFenetre);
    //void SetRenderWindow(sf::RenderWindow &mynewWindow);
    float Shoot(sf::Vector2f TargetPosition, sf::RenderWindow &myRenderWindow);
    sf::Vector2i GetWindowPosition(sf::RenderWindow &theRenderWindow) const;
    sf::Text getLifeHud();
    sf::Text getScoreHud();
    void setSizeWindowHud(sf::Vector2f sizeWindow);
    ~Player();

private:

    bool IamImmune;
    float rayon, ImmuneTime;
    //Immunity Timer
    unsigned long Score;
    unsigned short Life;
    Hud hud;
    //sf::RenderWindow myWindow;

    std::string PlayerName;
};

#endif // PLAYER_HPP_INCLUDED
