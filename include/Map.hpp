#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <list>
#include <map>
#include <string>

#include "Bullet.hpp"
#include "Engine.hpp"
#include "Zombie.hpp"
#include "Obstacle.hpp"

class Map
{
    std::vector<Bullet> AllBullets;
    std::vector<Zombie> ZombieArray;
    std::list<Obstacle> lObstacles;

    std::map<std::string, sf::Texture> mObstacleTextures;

    int width;
    int height;


    sf::Texture backgroundTexture;
    sf::Sprite background;

    std::string theme;

public:

    Map(std::string mapPath);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    void addBullet(Bullet bullet);
    void addZombie(Zombie newZombie);
    void addObstacle(std::string obstacleTexturePath, int x, int y);

    std::string getTheme() const;

    void drawObstacles(sf::RenderWindow* window) const;
    void update(sf::RenderWindow* game);

    sf::Sprite getBackground() const;

    sf::FloatRect getCollisionBox() const;

    std::list<Obstacle> getListeObstacles() const;

};



#endif // MAP_HPP_INCLUDED
