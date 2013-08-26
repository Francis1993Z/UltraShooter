#include "Weapon.hpp"

using namespace std;
using namespace sf;

Weapon::Weapon(bool p_tirIllimity, unsigned int p_ammunitions, sf::Vector2f pos){

    tirIllimity = p_tirIllimity;
    ammunitions = p_ammunitions;
    ancrage=pos;
}

void Weapon::fire()
{

}

void Weapon::fire(sf::Vector2f target_position)
{

}

void Weapon::refresh()
{

}

void Weapon::update()
{

}

void Weapon::updatePosition()
{

        targetdata t_data = user->getTarget();

    //cout<<"angle : "<<-(angle*180/M_PI)<<endl;
    setRotation(-(t_data.angle*180/M_PI)+90);

sf::Vector2f NewTurretPosition;
  NewTurretPosition.x=((cos(user->getRotation()*M_PI/180)))+(user->getOrigin().x - ancrage.x) + user->getPosition().x;
  NewTurretPosition.y=(-(sin(user->getRotation()*M_PI/180)))+(user->getOrigin().y - ancrage.y) + user->getPosition().y;
  //cout<<"NewTurretPosition.x : "<<NewTurretPosition.x<<" NewTurretPosition.y : "<<NewTurretPosition.y<<endl;
  setPosition(NewTurretPosition);
}

bool Weapon::isUpdatable() const
{
    return needRefresh;
}

Texture* Weapon::getSymbole(){

    return &symbole;
}

bool Weapon::isTirIllimity() const{

 return tirIllimity;
}

unsigned int Weapon::getAmmunitions() const{

    return ammunitions;
}

Weapon::~Weapon()
{

}
