#include "Ennemy.hpp"

using namespace std;

Ennemy::Ennemy(sf::Vector2f init_Position, Player& init_Target, long n_vie, TEAM team): Entity(n_vie, team)
{
    my_behaviour=STANDBY;
    setPosition(init_Position);
    my_target = &init_Target;
}
/*
Ennemy::Ennemy(Ennemy const& Ennemytocopy) : vie(Ennemytocopy.vie), damage(Ennemytocopy.damage),
 kill_point(Ennemytocopy.kill_point), my_target(Ennemytocopy.my_target),
 my_behaviour(Ennemytocopy.my_behaviour)
{

}
*/
void Ennemy::update()
{
    cout<<"virtual update ennemy"<<endl;
}

unsigned int Ennemy::die() const
{
    cout<<"virtual die ennemy"<<endl;
    return 1;
}


void Ennemy::ChangeBehaviour(Behaviour NewBehaviour)
{
    my_behaviour=NewBehaviour;
}

void Ennemy::SetTarget(Player &NewTarget)
{
    my_target=&NewTarget;
}


Ennemy* Ennemy::getAdresse()
{
    return  this;
}



int Ennemy::getKillPoint() const
{
    return kill_point;
}


