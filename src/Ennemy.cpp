#include "Ennemy.hpp"

void Ennemy::ChangeBehaviour(Behaviour NewBehaviour)
{
    my_behaviour=NewBehaviour;
}

void Ennemy::SetTarget(Player &NewTarget)
{
    my_target=&NewTarget;
    //cout<<"Bot : "<<this<<" Target : "<<my_target<<endl;
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
