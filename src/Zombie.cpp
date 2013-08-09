#include "Zombie.hpp"

#include <iostream>

using namespace std;
using namespace sf;


Zombie::Zombie(sf::Vector2f init_Position, Player& init_Target, TEAM team)
    :Ennemy(init_Position, init_Target, 1, team)
{

    sf::Vector2f my_size;
    my_size.x=25;
    my_size.y=25;
    setSize(my_size);
    setOrigin(Vector2f(25/2,25/2));
    setFillColor(Color::Red);


    damage = 5;
    kill_point = 10;

    e_m = 8;
    e_mx = e_m;
    e_my = e_m;
    m_fx=0.00f;
    m_fy=0.00f;
    d_radius = 25/2;
    //my_behaviour = ATTACK;
    my_behaviour = STANDBY;
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
    if(my_behaviour == STANDBY)
        {
            float mvx;
            float mvy;

            Vector2f v;
            v.x = 0.00f;
            v.y = 0.00f;
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
