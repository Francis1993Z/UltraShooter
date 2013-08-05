#ifndef LASERBEAM_HPP_INCLUDED
#define LASERBEAM_HPP_INCLUDED

#include "Projectile.hpp"
#include "Entity.hpp"
#include <list>

//! Les Laserbeam sont des projectiles de type SEGMENT

class Laserbeam : public Projectile
{
private :
    const Entity& m_user;

    Laserbeam** m;
public:
    Laserbeam(sf::Vector2f init_position, Entity const& user, TEAM team);
    void setm(Laserbeam*& my_m);
    void UpdatePosition();
    void setI(sf::Vector2f new_I);
    sf::Vector2f getI() const;
    ~Laserbeam();
};

#endif // LASERBEAM_HPP_INCLUDED
