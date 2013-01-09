#ifndef ENNEMI_H_INCLUDED
#define ENNEMI_H_INCLUDED

#include "PreHeader.h"
#include "Entity.hpp"

class Ennemi : public Entity
    {
    public:
        Ennemi(float X, float Y, sf::Color Couleur, float Rayon, float Bordure, sf::Color CouleurBordure);
void ApplyVelocity(sf::Vector2f velocity);
void Update();
void Update(float x, float y);
void UpdateEvent(sf::RenderWindow &f_App);
void SetTarget(Entity &NewTarget);
void ChangeBehaviour(Behaviour NewBehaviour);
int GetKillPoint() const;
sf::Shape GetShape() const;
sf::Vector2f GetPosition() const;
    float GetRayon() const;
Ennemi* MyAdress();

    private:
        float rayon;
        int killpoint;
    sf::Vector2f Velocity;
    sf::Shape EnnemiShape;
    };

#endif // ENNEMI_H_INCLUDED
