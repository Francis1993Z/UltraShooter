#ifndef LASERBEAM_HPP_INCLUDED
#define LASERBEAM_HPP_INCLUDED

#include "Projectile.hpp"
#include "Entity.hpp"
#include <list>

class Laserbeam : public Projectile
{
private :
const Entity& m_user;
Laserbeam** m;
public:
    Laserbeam(sf::Vector2f init_position, Entity const& user, TEAM team);
    void setm(Laserbeam*& my_m);
    void UpdatePosition();
    ~Laserbeam();
};

#endif // LASERBEAM_HPP_INCLUDED
