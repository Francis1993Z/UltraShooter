#include "LaserWeapon.hpp"
#include "Engine.hpp"

using namespace sf;

LaserWeapon::LaserWeapon(Entity const& my_user)
{
needRefresh=true;
my_laserbeam=nullptr;
}

    void LaserWeapon::fire()
    {
            my_laserbeam = new Laserbeam(user->getPosition(), *user, user->getTeam());//need team in constructor
            Engine::getInstance()->getMap()->addProjectile(my_laserbeam);
    }

void LaserWeapon::refresh()
{
    stopLaserBeam();
}

void LaserWeapon::stopLaserBeam()
{
Engine::getInstance()->getMap()->rmProjectile(*my_laserbeam);
my_laserbeam=nullptr;
}

    LaserWeapon::~LaserWeapon()
    {

    }

