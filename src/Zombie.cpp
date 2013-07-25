#include "Zombie.hpp"

#include <iostream>

using namespace std;
using namespace sf;


Zombie::Zombie(sf::Vector2f init_Position, Player& init_Target)
    :Ennemy(init_Position, init_Target)
{

    sf::Vector2f my_size;
    my_size.x=50;
    my_size.y=50;
    setSize(my_size);
    setOrigin(Vector2f(25,25));
    setFillColor(Color::Red);

    vie = 1;
    damage = 5;
    kill_point = 10;

    e_m = 8;
    e_mx = e_m;
    e_my = e_m;

    d_radius = 25;
    my_behaviour = ATTACK;
    //cout << "New Zombie at : " << this << endl;
}

void Zombie::update()
{
    if(my_behaviour == ATTACK)
        {
            float mvx;
            float mvy;

            Vector2f Myposition = getPosition(), Targetposition = my_target->getPosition();
            //float TargetDirection = GetAngle(Myposition.x, Myposition.y, Targetposition.x, Targetposition.y); référence indéfinie vers GetAngle() je ne comprends pas pourquoi
            Vector2f vec1 = Myposition;
            Vector2f vec2 = Targetposition;
            float a = vec2.x - vec1.x;
            float o = vec2.y - vec1.y;
            float TargetDirection;
            TargetDirection = atan2(-o, a);
            setRotation(-(TargetDirection*180/M_PI));
            Vector2f v;
            v.x = cos(TargetDirection) * e_mx;
            v.y = sin(TargetDirection) * e_my;
            //std::cout<<this<<" : x : "<<Myposition.x<<" y : "<<Myposition.y<<" angle : "<<TargetDirection<<std::endl;

            mvx = v.x + m_fx;
            mvy = v.y + m_fy;

            move(mvx, -mvy);

            m_fy = 0;
            m_fx = 0;
        }
}

unsigned int Zombie::die() const
{
    return getKillPoint();
}
