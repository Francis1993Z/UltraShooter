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

Ennemy* Ennemy::getAdresse()
{
    return  this;
}
