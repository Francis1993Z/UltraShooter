#include "Bullet.hpp"

using namespace std;
using namespace sf;

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle)
{
    Bullet::setFillColor(sf::Color::White);
    Bullet::setPosition(myInitPosition);
    Bullet::setRadius(5);
    Bullet::setOrigin(2.5f, 2.5f);
    damage=15;
    vitesse=25;
    angle=myangle;
}

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle, sf::Color myColor, int myDamage, float myvitesse)
{
    Bullet::setFillColor(myColor);
    Bullet::setPosition(myInitPosition);
    damage=myDamage;
    vitesse=myvitesse;
    angle=myangle;
}

void Bullet::UpdatePosition()
{
    float vx, vy;

    vx=cos(angle) * vitesse;
    vy=sin(angle) * vitesse;
    Bullet::move(vx, -vy);
}


Bullet::~Bullet()
{

}
