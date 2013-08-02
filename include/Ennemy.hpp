#ifndef ENNEMY_HPP_INCLUDED
#define ENNEMY_HPP_INCLUDED

#include "Player.hpp"

enum Behaviour {STANDBY, ATTACK, ESCAPE, FOLLOW};

class Ennemy : public Entity
{
public:

    Ennemy(sf::Vector2f init_Position, Player& init_Target, long n_vie, TEAM team);
    Ennemy(Ennemy const& Ennemytocopy);
    void update();
    unsigned int die() const;
    void SetTarget(Player &NewTarget);
    void ChangeBehaviour(Behaviour NewBehaviour);
    int getKillPoint() const;


    float get_dRadius() const;
    float getSpeed() const;

    Ennemy* getAdresse();

protected:

    int kill_point;

    Player *my_target;
    Behaviour my_behaviour;

};

#endif // ENNEMY_HPP_INCLUDED
