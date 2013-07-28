#include "Bullet.hpp"

using namespace std;
using namespace sf;

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle, TEAM y_TEAM)
{
    setFillColor(sf::Color::White);
    setPosition(myInitPosition);
    setRadius(5);
    setOrigin(2.5f, 2.5f);
    damage=15;
    vitesse=25;
    angle=myangle;
    my_team=y_TEAM;
}

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle, sf::Color myColor, int myDamage, float myvitesse, TEAM y_TEAM)
{
    setFillColor(myColor);
    setPosition(myInitPosition);
    damage=myDamage;
    vitesse=myvitesse;
    angle=myangle;
      my_team=y_TEAM;
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
