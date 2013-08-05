#include "Entity.hpp"
#include <iostream>
#include "Engine.hpp"

using namespace std;
using namespace sf;

void Entity::subirDegats(unsigned int p_damage)
{
    modifierVie(-p_damage);
}

bool Entity::alive() const
{
    if (vie > 0) return true;
    return false;
}

void Entity::modifierVie(int pv)
{
    vie+=pv;
}

sf::FloatRect Entity::getCollisionBox()
{
    return getGlobalBounds();
}

TEAM Entity::getTeam() const
{
    return my_team;
}

void Entity::ApplyForce(float fx, float fy)
{
    m_fx=+fx;
    m_fy=+fy;
}

float Entity::get_dRadius() const
{
    return d_radius;
}


float Entity::getSpeed() const
{
    return e_m;
}

long Entity::getVie() const
{
    return vie;
}

unsigned int Entity::getDamage() const
{
    return damage;
}

targetdata Entity::getTarget() const
{
    cout<<"virtual getTarget"<<endl;
    sf::Vector2f v2f(0.00f, 0.00f);
    targetdata data;
    data.angle=0.00f;
    data.position=v2f;
    return data;
}

Vector2i Entity::GetWindowPosition() const
{
    return Engine::getInstance()->getRenderWindow()->mapCoordsToPixel(Entity::getPosition(), Engine::getInstance()->getRenderWindow()->getView());
}

void Entity::update()
{
    cout<<"virtual update"<<endl;
}

unsigned int Entity::die() const
{
    cout<<"virtual die"<<endl;
    return 1;
}
