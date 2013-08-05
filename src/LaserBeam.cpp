#include "LaserBeam.hpp"
#include <iostream>

using namespace std;
using namespace sf;


Laserbeam::Laserbeam(sf::Vector2f init_position, Entity const& user, TEAM team) : m_user(user)
{
    setPosition(init_position);
    setSize(sf::Vector2f(3.00f, 6000.00f));
    setOrigin(5.00f, 0.00f);
    setFillColor(sf::Color::Blue);
    my_collisiontype=SEGMENT;
    my_team=team;
}


void Laserbeam::UpdatePosition()
{
    targetdata t_data = m_user.getTarget();
    sf::Vector2i user_window_position = m_user.GetWindowPosition();
    sf::Vector2f target_position = t_data.position, user_position = m_user.getPosition();
    //cout<<"user position x : "<<user_position.x<<" y : "<<user_position.y<<endl;
    //cout<<"target position x : "<<target_position.x<<" y : "<<target_position.y<<endl;

    sf::Vector2f converted_user_position;
    converted_user_position.x = (float)user_window_position.x;
    converted_user_position.y = (float)user_window_position.y;
    float x1 = converted_user_position.x;
    float y1 = converted_user_position.y;

    float x2 = target_position.x;
    float y2 = target_position.y;

    float a = x2 - x1;
    float o = y2 - y1;
    float angle = atan2(-o, a);
    //cout<<"angle : "<<-(angle*180/M_PI)<<endl;
    setPosition(user_position);
    setRotation(-(angle*180/M_PI)-90);
}

void Laserbeam::setm(Laserbeam*& my_m)
{
    m=&my_m;
}

Laserbeam::~Laserbeam()
{
*m=NULL;

}
