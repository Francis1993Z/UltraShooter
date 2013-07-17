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

int Ennemy::getVie() const
{

    return vie;
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

void Ennemy::takeDamage(unsigned int damage)
{
    vie=-damage;
}

bool Ennemy::alive() const
{
    if (vie > 0)
        return true;
    else if(vie < 0)
        return false;
}

int Ennemy::getKillPoint() const
{
    return kill_point;
}

float Ennemy::getSpeed() const
{
    return e_m;
}

void Ennemy::subirDegats(unsigned int p_damage)
{

    vie-=p_damage;
}


sf::FloatRect Ennemy::getCollisionBox() const
{

    return getGlobalBounds();
}
