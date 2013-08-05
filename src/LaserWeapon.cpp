#include "LaserWeapon.hpp"
#include "Engine.hpp"
#include <iostream>

using namespace std;
using namespace sf;

LaserWeapon::LaserWeapon(Entity const& my_user)
{
    needRefresh=true;
    my_laserbeam=NULL;
    user=&my_user;

}

void LaserWeapon::fire()
{
    my_laserbeam = new Laserbeam(user->getPosition(), *user, user->getTeam());
    Engine::getInstance()->getMap()->addProjectile(my_laserbeam);
}

void LaserWeapon::refresh()
{
    if(my_laserbeam!=NULL)
        stopLaserBeam();
}

void LaserWeapon::stopLaserBeam()
{
    cout<<"laserbeam to remove : "<<my_laserbeam<<endl;
    Engine::getInstance()->getMap()->rmProjectile(my_laserbeam);
    my_laserbeam=NULL;
}

LaserWeapon::~LaserWeapon()
{

}

