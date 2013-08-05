#include "Projectile.hpp"

using namespace std;
using namespace sf;

collisiontype Projectile::getCollisionType() const
{
    return my_collisiontype;
}

unsigned int Projectile::getDamage() const
{
    return damage;
}


void Projectile::UpdatePosition()
{

}

TEAM Projectile::getTeam() const
{
    return my_team;
}

void Projectile::setI(Vector2f new_I)
{
    I=new_I;
}

Vector2f Projectile::getI() const
{
    return I;
}

Projectile::~Projectile()
{

}
