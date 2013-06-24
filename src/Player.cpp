#include "Player.hpp"
#include "GlobalFunctions.h"
using namespace std;
using namespace sf;


 Player::Player(sf::Vector2f init_position)
{
rayon=50.f;
Player::setRadius(rayon);
Player::setFillColor(sf::Color::Blue);
Player::setPosition(init_position);
Player::setOrigin(50.f, 50.f);
}

void Player::SetRenderWindow(const sf::RenderWindow &mynewWindow)
{
myWindow=mynewWindow;

}

float Player::Shoot(sf::Vector2f TargetPosition)
{

float x1=Player::getPosition().x;
float y1=Player::getPosition().y;
float x2=TargetPosition.x;
float y2=TargetPosition.y;
    float a=x2-x1;
    float o=y2-y1;
    float angle;
return  angle = atan2(-o, a);



//return GetAngle_v2f(Player::getPosition(), TargetPosition);
}

 Player::~Player()
{

}
