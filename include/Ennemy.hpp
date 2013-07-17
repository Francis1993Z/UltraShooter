#ifndef ENNEMY_HPP_INCLUDED
#define ENNEMY_HPP_INCLUDED

#include "Player.hpp"



enum Behaviour {STANDBY, ATTACK, ESCAPE, FOLLOW};

class Ennemy : public sf::RectangleShape
{

public:

    Ennemy(sf::Vector2f init_Position, Player& init_Target);

    virtual void update();
    virtual unsigned int die() const;
    void ApplyForce(float fx, float fy);
    void SetTarget(Player &NewTarget);
    void ChangeBehaviour(Behaviour NewBehaviour);
    void subirDegats(unsigned int p_damage);
    void takeDamage(unsigned int damage);

    unsigned int getDamage() const;
    int getKillPoint() const;
    int getVie() const;

    float get_dRadius() const;
    float getSpeed() const;
    sf::FloatRect getCollisionBox() const;
    bool alive() const;

    Ennemy* getAdresse();

protected:


    int vie;
    int damage;
    int kill_point;

    Player *my_target;
    Behaviour my_behaviour;

    float d_radius, m_fx, m_fy;
    float e_m,e_mx, e_my;

};

#endif // ENNEMY_HPP_INCLUDED
