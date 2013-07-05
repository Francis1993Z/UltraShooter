#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Bullet.hpp"
#include "Engine.hpp"
#include "Zombie.hpp"

class Map
{
    std::vector<Bullet> AllBullets;
    std::vector<Zombie> ZombieArray;

    int width;
    int height;

    sf::Texture backgroundTexture;
    sf::Sprite background;

public:

    Map(std::string mapPath);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    void addBullet(Bullet bullet);
    void addZombie(Zombie newZombie);
    void update(sf::RenderWindow& game);

    sf::Sprite getBackground() const;

};



#endif // MAP_HPP_INCLUDED
