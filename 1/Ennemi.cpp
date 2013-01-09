#include "Ennemi.h"

using namespace std;
using namespace sf;



Ennemi::Ennemi(float X, float Y, sf::Color Couleur, float Rayon, float Bordure, sf::Color CouleurBordure)
{
    rayon=Rayon;
    sf::Shape Circle = Shape::Circle(0, 0, rayon, Couleur, Bordure, CouleurBordure);
    Circle.SetPosition(X,Y);
    EnnemiShape = Circle;
    killpoint=25;
    Velocity.x=0.00f;
    Velocity.y=0.00f;
    MyBehaviour=STANDBY;
}

void Ennemi::ApplyVelocity(sf::Vector2f velocity)
{
    Velocity = velocity;
}

void Ennemi::Update()
{
    if(MyBehaviour==ATTACK)
    {
        sf::Vector2f Myposition = EnnemiShape.GetPosition(), Targetposition = MyTarget->GetPosition();
        float TargetDirection = GetAngle(Myposition.x, Myposition.y, Targetposition.x, Targetposition.y);
        Velocity.x=cos(TargetDirection) * 8;
        Velocity.y=sin(TargetDirection) * 8;
        EnnemiShape.Move(Velocity.x, -Velocity.y);
    }

}

sf::Shape Ennemi::GetShape() const
{
    return EnnemiShape;
}

sf::Vector2f Ennemi::GetPosition() const
{
    return EnnemiShape.GetPosition();
}

float Ennemi::GetRayon() const
{
    return rayon;
}

void Ennemi::ChangeBehaviour(Behaviour NewBehaviour)
{
    MyBehaviour=NewBehaviour;
}

void Ennemi::SetTarget(Entity &NewTarget)
{
    MyTarget=&NewTarget;
    //cout<<"Bot : "<<this<<" Target : "<<MyTarget<<endl;
}

Ennemi* Ennemi::MyAdress()
{
    return  this;
}

int Ennemi::GetKillPoint() const
{
    return killpoint;
}

