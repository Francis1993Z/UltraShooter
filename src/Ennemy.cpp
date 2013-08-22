#include "Ennemy.hpp"

using namespace std;

Ennemy::Ennemy(sf::Vector2f init_Position, Entity& init_Target, long n_vie, TEAM team): Entity(n_vie, team)
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

void Ennemy::SetTarget(Entity &NewTarget)
{
    my_target=&NewTarget;
}

Ennemy* Ennemy::getAdresse()
{
    return  this;
}

targetdata Ennemy::getTarget() const
{
    float x1 = getPosition().x;
    float y1 = getPosition().y;

    float x2 = my_target->getPosition().x;
    float y2 = my_target->getPosition().y;

    float a = x2 - x1;
    float o = y2 - y1;
    float angle = atan2(-o, a);

    targetdata data;
    data.angle=angle;
    data.position=my_target->getPosition();
    return data;
}

int Ennemy::getKillPoint() const
{
    return kill_point;
}

Bonus* Ennemy::getBonus(){

    return new Bonus(getPosition());
}
