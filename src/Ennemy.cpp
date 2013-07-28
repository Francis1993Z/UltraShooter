#include "Ennemy.hpp"

using namespace std;

Ennemy::Ennemy(sf::Vector2f init_Position, Player& init_Target)
{
    setPosition(init_Position);
    my_target = &init_Target;
}

void Ennemy::update()
{
    cout<<"virtual update"<<endl;
}

unsigned int Ennemy::die() const
{
    cout<<"virtual die"<<endl;
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



unsigned int Ennemy::getDamage() const
{

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



int Ennemy::getKillPoint() const
{
    return kill_point;
}

float Ennemy::getSpeed() const
{

    return e_m;
}



