#include "Player.hpp"
#include "GlobalFunctions.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;

const float Player::vitesse = 15.0f;


Player::Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f sizeWindow):Life(100), Score(0), hud(Life, Score, font, sizeWindow)
{
    rayon=50.f;

    setRadius(rayon);
    setFillColor(sf::Color::Blue);
    setPosition(init_position);
    setOrigin(50.f, 50.f);
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

void Player::change_Weapon(int delta)
{
    int weapon_size=(int)my_weapon.size();
    if(delta>0)
        {
            if(actual_weapon==weapon_size-1) actual_weapon=0;
            else actual_weapon++;
        }
    else if(delta<0)
        {
            if(actual_weapon==0) actual_weapon=weapon_size-1;
            else actual_weapon--;
        }
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

sf::FloatRect Player::getCollisionBox()
{

    return getGlobalBounds();
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

bool Player::alive() const
{
    if (Life > 0)
        return true;

    return false;
}

void Player::subirDegats(unsigned int p_damage)
{

    modifierVie(-p_damage);
}

Player::~Player()
{

}
