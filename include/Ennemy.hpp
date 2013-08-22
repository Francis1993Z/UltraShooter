#ifndef ENNEMY_HPP_INCLUDED
#define ENNEMY_HPP_INCLUDED

#include "Entity.hpp"//attention
#include "Bonus.hpp"

enum Behaviour {STANDBY, ATTACK, ESCAPE, FOLLOW};

class Ennemy : public Entity
{
public:

    Ennemy(sf::Vector2f init_Position,  Entity& init_Target, long n_vie, TEAM team);
    Ennemy(Ennemy const& Ennemytocopy);
    void update();
    unsigned int die() const;
    void SetTarget(Entity &NewTarget);
    void ChangeBehaviour(Behaviour NewBehaviour);
    int getKillPoint() const;
    Bonus* getBonus();
targetdata getTarget() const;
    float get_dRadius() const;
    float getSpeed() const;

    Ennemy* getAdresse();

protected:

    int kill_point;

     Entity *my_target;
    Behaviour my_behaviour;

};

#endif // ENNEMY_HPP_INCLUDED
