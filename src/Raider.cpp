#include "Raider.hpp"

#include <iostream>

using namespace std;
using namespace sf;


Raider::Raider(sf::Vector2f init_Position, Player& init_Target, TEAM team) : Ennemy(init_Position, init_Target, 100, team)
{

 setTexture(*TextureManager::getTexture(getCWD()+"/ressources/ship/Raider.bmp"));

        sf::Image tmpimg = image_manager::get_image(getCWD()+"/ressources/ship/Raider.bmp");
    sf::Vector2u my_sizeu = tmpimg.getSize();
    sf::Vector2f my_sizef;
    my_sizef.x = (float)my_sizeu.x;
    my_sizef.y = (float)my_sizeu.y;
    setPosition(init_Position);
    setOrigin(my_sizef.x/2, my_sizef.x/2);

sf::Vector2f ancrage = EntityWithWeapon::searchhotspot(tmpimg);

    damage = 5;
    kill_point = 15;

    e_m = 8;
    e_mx = e_m;
    e_my = e_m;
    m_fx=0.00f;
    m_fy=0.00f;
    d_radius = my_sizef.x/2;
    //my_behaviour = ATTACK;
    my_behaviour = ATTACK;
    actual_weapon=0;
    my_weapon.push_back(new AutomaticWeapon(*this, true, 0, ancrage));
}


void Raider::update()
{
                my_weapon.at(actual_weapon)->updatePosition();



                   if(my_weapon.at(actual_weapon)->isUpdatable())
        {
                     my_weapon.at(actual_weapon)->update();
        }
    if(my_behaviour == ATTACK)
        {

            float mvx;
            float mvy;

            Vector2f Myposition = getPosition(), Targetposition = my_target->getPosition();
            //float TargetDirection = GetAngle(Myposition.x, Myposition.y, Targetposition.x, Targetposition.y); référence indéfinie vers GetAngle() je ne comprends pas pourquoi

            float TCoteopposer=Targetposition.y-Myposition.y;
            float TCoteadjacent=Targetposition.x-Myposition.x;
            float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
            float distance_target = sqrt(Tracinecarre);


            Vector2f vec1 = Myposition;
            Vector2f vec2 = Targetposition;
            float a = vec2.x - vec1.x;
            float o = vec2.y - vec1.y;
            float TargetDirection;
            TargetDirection = atan2(-o, a);
            setRotation(-(TargetDirection*180/M_PI)+90);


            if(distance_target > 350)
                {


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
            else
                {
                    my_weapon.at(actual_weapon)->fire(Targetposition);
                }

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

unsigned int Raider::die() const
{
    return getKillPoint();
}
