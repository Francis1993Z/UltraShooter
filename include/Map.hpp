#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "Bullet.hpp"
#include "Engine.hpp"

class Map
{
    std::vector<Bullet> AllBullets;

public:

    Map();
    ~Map();
    void addBullet(Bullet bullet);
    void update(sf::RenderWindow& game);

};



#endif // MAP_HPP_INCLUDED
