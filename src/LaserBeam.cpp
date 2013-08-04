#include "LaserBeam.hpp"

using namespace std;
using namespace sf;


Laserbeam::Laserbeam(sf::Vector2f init_position)
{
    setPosition(init_position);
    setSize(sf::Vector2f(3.00f, 6000.00f));
    setOrigin(5.00f, 0.00f);
    setFillColor(sf::Color::Blue);
}

void Laserbeam::setdamage(int d)
{
    damage=d;
}

Laserbeam::~Laserbeam()
{

}
