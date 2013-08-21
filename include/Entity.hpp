#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "GlobalFunctions.h"
#include "TextureManager.h"


class Entity : public sf::RectangleShape
{

protected:

    Entity(long c, TEAM team) : vie(c), my_team(team) { }

    long vie;///Points de vie
    unsigned int damage;
    //!
    ///d_radius donne une distance utile qui peut servire
    ///dans plusieurs cas, mais le plus souvant pour la repulsion ou les collisions.
    float d_radius, m_fx, m_fy;
    float e_m,e_mx;//vitesse
    float e_my;

public:
    TEAM getTeam() const;///recuperer dans quel equipe on est
    sf::FloatRect getCollisionBox();
    void subirDegats(unsigned int p_damage);///diminue les points de vie
    virtual void modifierVie(int pv);///modifie les points de vie
    bool alive() const;///Savoir si l'objet est encore en vie
    long getVie() const;///Recuperer les points de vie actuels
    float getSpeed() const;///Connaitre la vitesse
    void ApplyForce(float fx, float fy);
    float get_dRadius() const;
    unsigned int getDamage() const;
    virtual unsigned int die() const;///fait mourir l'objet et donne acces a son effet de mort specifique
    virtual void update();
    sf::Vector2i GetWindowPosition() const;
    virtual targetdata getTarget() const;
    TEAM my_team;
};

#endif // ENTITY_HPP_INCLUDED
