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
    if(my_laserbeam==NULL)
        {
            my_laserbeam = new Laserbeam(user->getPosition(), *user, user->getTeam());
            my_laserbeam->setm(my_laserbeam);
            Engine::getInstance()->getMap()->addProjectile(my_laserbeam);
            cout<<"new laser"<<endl;
        }


}

void LaserWeapon::refresh()
{

    if(my_laserbeam!=NULL)
        {
            stopLaserBeam();
        }

}

void LaserWeapon::stopLaserBeam()
{
    Engine::getInstance()->getMap()->rmProjectile(my_laserbeam);
    my_laserbeam=NULL;
}


LaserWeapon::~LaserWeapon()
{

}

