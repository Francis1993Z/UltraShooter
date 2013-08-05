#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"


class Entity : public sf::RectangleShape
{

protected:

    Entity(long c, TEAM team) : vie(c), my_team(team) { }

    long vie;
    unsigned int damage;
    float d_radius, m_fx, m_fy;
    float e_m,e_mx;
    float e_my;

public:
    TEAM getTeam() const;
    sf::FloatRect getCollisionBox();
    void subirDegats(unsigned int p_damage);
    virtual void modifierVie(int pv);
    bool alive() const;
    long getVie() const;
    float getSpeed() const;
    void ApplyForce(float fx, float fy);
    float get_dRadius() const;
    unsigned int getDamage() const;
    virtual unsigned int die() const;
    virtual void update();
    sf::Vector2i GetWindowPosition() const;
    virtual targetdata getTarget() const;
    TEAM my_team;


};

#endif // ENTITY_HPP_INCLUDED
