#include "Projectile.h"

using namespace std;
using namespace sf;

bool Projectile::CIO()
{

    if(static_cast<unsigned int>(ProjectileSprite.GetPosition().x) < 0 ||
            static_cast<unsigned int>(ProjectileSprite.GetPosition().x) > WinWidth ||
            static_cast<unsigned int>(ProjectileSprite.GetPosition().y) < 0 ||
            static_cast<unsigned int>(ProjectileSprite.GetPosition().y)>WinHeight)
    {

        return true;

    }
    else
    {

        return false;

    }
}

Shape Projectile::GetProjectileSprite() const
{
    return ProjectileSprite;
}

Vector2f Projectile::GetPosition() const
{
    return ProjectileSprite.GetPosition();
    }
