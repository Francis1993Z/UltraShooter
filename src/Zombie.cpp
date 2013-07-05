#include "Zombie.hpp"


Zombie::Zombie(sf::Vector2f init_Position, Player& init_Target)
{
Zombie::setRadius(50);
Zombie::setOrigin(sf::Vector2f(25,25));
Zombie::setPosition(init_Position);
Zombie::setFillColor(sf::Color::Red);
my_behaviour=ATTACK;
my_target=&init_Target;
}

void Zombie::Update()
{
    if(my_behaviour==ATTACK)
    {
        sf::Vector2f Myposition = Zombie::getPosition(), Targetposition = my_target->getPosition();
        //float TargetDirection = GetAngle(Myposition.x, Myposition.y, Targetposition.x, Targetposition.y); référence indéfinie vers GetAngle() je ne comprends pas pourquoi
       sf::Vector2f vec1=Myposition;
       sf::Vector2f vec2=Targetposition;
    float a=vec2.x-vec1.x;
    float o=vec2.y-vec1.y;
    float TargetDirection;

    TargetDirection = atan2(-o, a);
       sf::Vector2f v;
        v.x=cos(TargetDirection) * 8;
        v.y=sin(TargetDirection) * 8;
                std::cout<<this<<" : x : "<<Myposition.x<<" y : "<<Myposition.y<<" angle : "<<TargetDirection<<std::endl;
        Zombie::move(v.x, -v.y);
    }
}
