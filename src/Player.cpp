#include "Player.hpp"
#include "GlobalFunctions.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;

const float Player::vitesse = 15.0f;

Player::Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f sizeWindow): Entity(100), Score(0), hud(vie, Score, font, sizeWindow)
{
    sf::Vector2f my_size;
    my_size.x=50;
    my_size.y=50;
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

float Player::getVitesse() const
{

    return vitesse;
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
    cout<<"fonction"<<endl;
}

unsigned long Player::getScore()
{
    return Score;
}

Player::~Player()
{

}
