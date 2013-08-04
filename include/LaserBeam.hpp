#ifndef LASERBEAM_HPP_INCLUDED
#define LASERBEAM_HPP_INCLUDED

#include "Projectile.hpp"

#include <list>

class Laserbeam : public Projectile, public sf::RectangleShape
{
private :


public:
    Laserbeam(sf::Vector2f init_position);
    void setdamage(int d);
    ~Laserbeam();
};

#endif // LASERBEAM_HPP_INCLUDED
