#include "Splitter.hpp"

using namespace std;
using namespace sf;

Splitter::Splitter(Vector2f init_Position, Player& init_Target, unsigned int level)
{
    float radius = 100;
    float n_radius = radius;

    my_level = level;

    e_m = 4;
    e_mx = e_m;
    e_my = e_m;

    kill_point = 5;

    if (level == 2)
    {
        n_radius = radius / 2;
        kill_point = kill_point * 2;

        e_mx = e_m * 2;
        e_my = e_m * 2;
    }
    else if (level == 3)
    {
        n_radius = radius / 4;
        kill_point = kill_point * 4;

        e_mx=e_m*4;
        e_my=e_m*4;
    }
    else if (level == 4)
    {
        n_radius = radius / 8;
        kill_point = kill_point * 8;

        e_mx=e_m*8;
        e_my=e_m*8;
    }

    cout << "e_m : " << e_m << endl;

    cout << "level : " << level << endl;

    setRadius(n_radius);
    setOrigin(Vector2f(n_radius / 2, n_radius / 2));
    setPosition(init_Position);
    setFillColor(Color::Green);

    d_radius=Splitter::getRadius();

    my_behaviour=ATTACK;
    my_target=&init_Target;

    Vector2f t_pos=my_target->getPosition();

    float a = t_pos.x-init_Position.x;
    float o = t_pos.y-init_Position.y;
    float angle = atan2(-o, a);

    float myrotation = angle;

    setRotation(myrotation);
}


unsigned int Splitter::getNextLevel() const
{
    return ++my_level;
}

unsigned int Splitter::getLevel() const
{
    return my_level;
}
