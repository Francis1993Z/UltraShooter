#ifndef HUD_H
#define HUD_H


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


#include <sstream>
#include "Weapon.hpp"

class Player;

class Hud
{

public:
    Hud();

    void updateLife(long n_life);
    void updateScore(unsigned long n_score);
    void updateActualWeapon(sf::Texture* p_symboleWeapon, bool p_tirIllimity, unsigned int p_ammunitions);
    void updateAmmunitions(bool p_tirIllimity, unsigned int p_ammunitions);
    void setSizeWindow(sf::Vector2f n_sizeWindow);
    void Move(float vx, float vy);
    void setPositionHud();
    void draw();
    sf::Text getLife();
    sf::Text getScore();
    void init(long n_life, unsigned long n_score, sf::Texture* p_symboleWeapon, bool p_tirIllimity, unsigned int p_ammunitions);

    ~Hud();

protected:
private:
    sf::Text t_life;
    sf::Text t_score;
    sf::Text t_ammunitions;
    sf::Font font;
    sf::RectangleShape fondBarreDeVie;
    sf::RectangleShape barreDeVie;

    sf::Sprite* symboleWeapon;

    sf::Vector2f sizeWindow;

    std::stringstream ss;
};

#endif // HUD_H
