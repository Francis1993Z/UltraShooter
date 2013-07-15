#include "Zombie.hpp"

#include <iostream>

using namespace std;

Zombie::Zombie()
{
Zombie::setRadius(50);
Zombie::setOrigin(sf::Vector2f(25,25));
Zombie::setPosition(10.00f, 10.00f);
Zombie::setFillColor(sf::Color::Red);

e_mx=2;
e_my=2;
kill_point=10;
vie=1;
damage=5;
d_radius=Zombie::getRadius();
my_behaviour=ATTACK;
my_target=0;
cout<<"Vous ne devriez pas construire un Zombie de cette façon"<<endl;
cout<<"New Zombie at : "<<this<<endl;
}

Zombie::Zombie(sf::Vector2f init_Position, Player& init_Target)
{
Zombie::setRadius(50);
Zombie::setOrigin(sf::Vector2f(25,25));
Zombie::setPosition(init_Position);
Zombie::setFillColor(sf::Color::Red);

vie=1;
damage=5;
kill_point=10;
e_m=8;
e_mx=e_m;
e_my=e_m;
d_radius=Zombie::getRadius();
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
        v.x=cos(TargetDirection) * e_mx;
        v.y=sin(TargetDirection) * e_my;
                //std::cout<<this<<" : x : "<<Myposition.x<<" y : "<<Myposition.y<<" angle : "<<TargetDirection<<std::endl;

float mvx = v.x+m_fx;
float mvy = v.y+m_fy;
cout<<mvx<<endl;

        Zombie::move(mvx, -mvy);
        m_fy=0;
        m_fx=0;

    }
}

sf::FloatRect Zombie::getCollisionBox() const{

    return getGlobalBounds();
}
