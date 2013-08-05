#include "Bullet.hpp"

using namespace std;
using namespace sf;

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle, TEAM team)
{
    setFillColor(sf::Color::White);
    setPosition(myInitPosition);
    setSize(sf::Vector2f(5, 5));
    setOrigin(2.5f, 2.5f);
    damage=15;
    vitesse=25;
    angle=myangle;
    my_team=team;
    my_collisiontype=POINT;
}

Bullet::Bullet(sf::Vector2f myInitPosition, float myangle, sf::Color myColor, int myDamage, float myvitesse, TEAM team)
{
    setFillColor(myColor);
    setPosition(myInitPosition);
    damage=myDamage;
    vitesse=myvitesse;
    angle=myangle;
    my_team=team;
    my_team=team;
    my_collisiontype=POINT;
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
