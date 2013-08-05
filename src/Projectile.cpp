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

Projectile::~Projectile()
{

}
