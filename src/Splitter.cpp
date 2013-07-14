#include "Splitter.hpp"

using namespace std;

Splitter::Splitter(sf::Vector2f init_Position, Player& init_Target, unsigned int level)
{
my_level=level;
    float radius=100;
     e_m=4;
            e_mx=e_m;
            e_my=e_m;
    float n_radius=radius;
kill_point=5;
    if (level==2)
        {
            n_radius=radius/2;
kill_point=kill_point*2;
            e_mx=e_m*2;
            e_my=e_m*2;
        }

    else if (level==3)
        {
            n_radius=radius/4;
kill_point=kill_point*4;
            e_mx=e_m*4;
            e_my=e_m*4;
        }

    else if (level==4)
        {
            n_radius=radius/8;
kill_point=kill_point*8;
            e_mx=e_m*8;
            e_my=e_m*8;
        }
        cout<<"e_m : "<<e_m<<endl;

cout<<"level : "<<level<<endl;

    Splitter::setRadius(n_radius);
    Splitter::setOrigin(sf::Vector2f(n_radius/2, n_radius/2));
    Splitter::setPosition(init_Position);
    Splitter::setFillColor(sf::Color::Green);


    d_radius=Splitter::getRadius();
    my_behaviour=ATTACK;
    my_target=&init_Target;


    sf::Vector2f t_pos=my_target->getPosition();


        float a=t_pos.x-init_Position.x;
    float o=t_pos.y-init_Position.y;
    float angle = atan2(-o, a);

     float myrotation = angle;


        Splitter::setRotation(myrotation);
}


unsigned int Splitter::getNextLevel() const
{
return my_level+1;
}

