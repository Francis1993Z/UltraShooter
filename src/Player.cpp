#include "Player.hpp"
#include "GlobalFunctions.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;



Player::Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f sizeWindow, TEAM team): Entity(10000, team), Score(0), hud(vie, Score, font, sizeWindow)
{
    e_m = 15.00f;
    e_mx = e_m;
    e_my = e_m;
    m_fx=0.00f;
    m_fy=0.00f;
    d_radius = 25;
    sf::Vector2f my_size;
    my_size.x=100;
    my_size.y=100;
    setSize(my_size);
    setFillColor(sf::Color::Blue);
    setPosition(init_position);
    setOrigin(my_size.x/2, my_size.x/2);
    actual_weapon=0;
    my_weapon.push_back(new AutomaticWeapon(*this));
    my_weapon.push_back(new ShrapnelWeapon(*this));

}

void Player::Shoot()
{
    my_weapon.at(actual_weapon)->fire();
}


Vector2i Player::GetWindowPosition(sf::RenderWindow &theRenderWindow) const
{
    return theRenderWindow.mapCoordsToPixel(Player::getPosition(), theRenderWindow.getView());
}

Text Player::getLifeHud()
{
    return hud.getLife();
}

Text Player::getScoreHud()
{
    return hud.getScore();
}

void Player::move_myhud(float vx, float vy)
{
    hud.Move(vx, vy);
}

void Player::setSizeWindowHud(Vector2f sizeWindow)
{
    hud.setSizeWindow(sizeWindow);
}

float Player::getRayon()
{

    return rayon;
}



void Player::addPoints(int points)
{
    Score+=points;

    hud.updateScore(Score);
}

void Player::modifierVie(int pv)//fonction Entity::modifierVie() masquée
{
    vie+=pv;
    hud.updateLife(vie);
}

unsigned long Player::getScore()
{
    return Score;
}

Player::~Player()
{

}
