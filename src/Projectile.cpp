#include "Projectile.hpp"

using namespace std;
using namespace sf;

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
