#include "Player.hpp"
#include "GlobalFunctions.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;

const float Player::vitesse = 15.0f;


Player::Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f sizeWindow): Score(0), hud(Life, Score, font, sizeWindow)
{
Life=100;
  sf::Vector2f my_size;
    my_size.x=50;
    my_size.y=50;
    setSize(my_size);
    setFillColor(sf::Color::Blue);
    setPosition(init_position);
    setOrigin(25.f, 25.f);
    actual_weapon=0;
    my_weapon.push_back(new AutomaticWeapon(*this));
    my_weapon.push_back(new ShrapnelWeapon(*this));
}

/*void Player::SetRenderWindow(sf::RenderWindow &mynewWindow)
{
mynewWindow.co;

}*/

void Player::Shoot()
{
    my_weapon.at(actual_weapon)->fire();
}

void Player::subirDegats(unsigned int p_damage)
{
    Life-=p_damage;
        hud.updateLife(Life);
}


bool Player::ReadyToShoot() const
{
    Int32 time=weapon_clock.getElapsedTime().asMilliseconds();

    if (time > 80)
        return true;
    else
        return false;
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

void Player::modifierVie(int pv)
{

    Life+=pv;

    hud.updateLife(Life);
}


Player::~Player()
{

}
