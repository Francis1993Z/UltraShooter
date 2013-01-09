#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Projectile.h"

class Bullet : public Projectile
{
public :

    Bullet(sf::Vector2f Initial_Position, int Damage,  float angle, sf::RenderWindow *APP);
    void UpdatePosition();
    float GetRayon() const;
    //bool TestCollision(Point tab[4]);
    int Hit() const;
    ~Bullet();
private:
    float rayon;
};


#endif // BULLET_H_INCLUDED
