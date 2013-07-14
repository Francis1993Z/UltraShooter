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
#include "Player.hpp"
#include "Engine.hpp"
#include "Zombie.hpp"
#include "Splitter.hpp"
#include "Obstacle.hpp"
#include "Wave.hpp"

class Map
{
    std::vector<Bullet> AllBullets;
    std::vector<Zombie> ZombieArray;
    std::vector<Splitter> SplitterArray;
    std::vector<Ennemy> EnnemyArray;

    std::list<Obstacle> lObstacles;
    std::list<Wave> lWaves;
    Player* player;

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
void setPlayer(Player& newPlayer);
    void addBullet(Bullet bullet);
    void addZombie(Zombie newZombie);
    void addSplitter(Splitter newSplitter);
    void addObstacle(std::string obstacleTexturePath, int x, int y);
    void addWave(Wave w);

    std::string getTheme() const;

    void drawObstacles(sf::RenderWindow* window) const;
    void update(sf::RenderWindow* game);

    sf::Sprite getBackground() const;

    sf::FloatRect getCollisionBox() const;

    std::list<Obstacle> getListeObstacles() const;

};



#endif // MAP_HPP_INCLUDED
