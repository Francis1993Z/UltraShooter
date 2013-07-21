#include "Bullet.hpp"

using namespace std;
using namespace sf;

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle)
{
    setFillColor(sf::Color::White);
    setPosition(myInitPosition);
    setRadius(5);
    setOrigin(2.5f, 2.5f);
    damage=15;
    vitesse=25;
    angle=myangle;
}

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle, sf::Color myColor, int myDamage, float myvitesse)
{
    setFillColor(myColor);
    setPosition(myInitPosition);
    damage=myDamage;
    vitesse=myvitesse;
    angle=myangle;
}

void Bullet::UpdatePosition()
{
    float vx, vy;

    vx=cos(angle) * vitesse;
    vy=sin(angle) * vitesse;
    move(vx, -vy);
}


Bullet::~Bullet()
{

}
