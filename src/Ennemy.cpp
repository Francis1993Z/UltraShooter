#include "Ennemy.hpp"

using namespace std;

void Ennemy::ChangeBehaviour(Behaviour NewBehaviour)
{
    my_behaviour=NewBehaviour;
}

void Ennemy::SetTarget(Player &NewTarget)
{
    my_target=&NewTarget;
    //cout<<"Bot : "<<this<<" Target : "<<my_target<<endl;
}

int Ennemy::getVie() const {

    return vie;
}

unsigned int Ennemy::getDamage() const{

    return damage;
}
void Ennemy::ApplyForce(float fx, float fy)
{
m_fx=+fx;
m_fy=+fy;
}

float Ennemy::get_dRadius() const
{
    return d_radius;
}

Ennemy* Ennemy::getAdresse()
{
    return  this;
}

void Ennemy::takeDamage(unsigned int damage)
{
vie=-damage;
}

bool Ennemy::alive() const
{
if (vie>0)    return true;
else if(vie<0) return false;
}

int Ennemy::getKillPoint() const
{
return kill_point;
}

float Ennemy::getSpeed() const
{
cout<<"e_m f : "<<e_m<<endl;
return e_m;
}

void Ennemy::subirDegats(unsigned int p_damage){

    vie-=p_damage;
}
