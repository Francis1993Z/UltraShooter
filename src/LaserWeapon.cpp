#include "LaserWeapon.hpp"
#include "Engine.hpp"
#include <iostream>

using namespace std;
using namespace sf;

LaserWeapon::LaserWeapon(Entity const& my_user, bool p_tirIllimity, unsigned int p_ammunitions, sf::Vector2f pos):Weapon(p_tirIllimity, p_ammunitions, pos)
{
            setTexture(*TextureManager::getTexture(getCWD()+"/ressources/turret/Laser.bmp"));

        sf::Image tmpimg = image_manager::get_image(getCWD()+"/ressources/turret/Laser.bmp");
    sf::Vector2u my_sizeu = tmpimg.getSize();
    sf::Vector2f my_sizef;
    my_sizef.x = (float)my_sizeu.x;
    my_sizef.y = (float)my_sizeu.y;
    setPosition(init_Position);
    setOrigin(my_sizef.x/2, my_sizef.x/2);

    needRefresh=true;
    my_laserbeam=NULL;
    user=&my_user;
    symbole = (*(Engine::getInstance()->getLoadFiles()->getSymboleLaserWeapon()));
}

void LaserWeapon::fire()
{
    if(my_laserbeam==NULL)
        {
            my_laserbeam = new Laserbeam(user->getPosition(), *user, user->getTeam());
            my_laserbeam->setm(my_laserbeam);
            Engine::getInstance()->getMap()->addProjectile(my_laserbeam);
            //cout<<"new laser"<<endl;
        }


}

void LaserWeapon::refresh()
{

    if(my_laserbeam!=NULL)
        {
            stopLaserBeam();
        }

}

void LaserWeapon::update()
{
                 if(my_laserbeam!=NULL)
        {
            Engine::getInstance()->getMusicManager()->playEvent("ressources/sounds/events/laserbeam1.flac");
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

