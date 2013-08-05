#include "LaserBeam.hpp"

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
sf::Vector2f user_position = m_user.getPosition();
sf::Vector2f target_position = t_data.position;

            float x1 = user_position.x;
            float y1 = user_position.y;

            float x2 = target_position.x;
            float y2 = target_position.y;

            float a = x2 - x1;
            float o = y2 - y1;
            float angle = atan2(-o, a);
            setPosition(user_position);
            setRotation(angle);
}


Laserbeam::~Laserbeam()
{

}
