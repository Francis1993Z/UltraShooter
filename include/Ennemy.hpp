#ifndef ENNEMY_HPP_INCLUDED
#define ENNEMY_HPP_INCLUDED

#include "Entity.hpp"

#include "Player.hpp"

enum Behaviour {STANDBY, ATTACK, ESCAPE, FOLLOW};

class Ennemy : public Entity
{

public:

    Ennemy(sf::Vector2f init_Position, Player& init_Target);

    virtual void update();
    virtual unsigned int die() const;
    void ApplyForce(float fx, float fy);
    void SetTarget(Player &NewTarget);
    void ChangeBehaviour(Behaviour NewBehaviour);


    unsigned int getDamage() const;
    int getKillPoint() const;

    float get_dRadius() const;
    float getSpeed() const;



    Ennemy* getAdresse();

protected:


    int damage;
    int kill_point;

    Player *my_target;
    Behaviour my_behaviour;

    float d_radius, m_fx, m_fy;
    float e_m,e_mx, e_my;

};

#endif // ENNEMY_HPP_INCLUDED
