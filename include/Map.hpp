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
#include "Ennemy.hpp"
#include "Player.hpp"
#include "Splitter.hpp"
#include "Raider.hpp"
#include "Obstacle.hpp"
#include "Wave.hpp"
#include "EnnemyFactory.hpp"

class Map
{
    std::vector<Bullet> AllBullets;
    std::vector<Ennemy *> EnnemyArray;

    std::list<Obstacle> lObstacles;
    std::list<Wave> lWaves;

    std::map<std::string, sf::Texture> mObstacleTextures;

    EnnemyFactory factory;

    int width;
    int height;


    sf::Texture backgroundTexture;
    sf::Sprite background;

    std::string theme;

    Ennemy* EnnemyTouche;
    Player* player;

    bool gameOver;

public:

    Map(std::string mapPath);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    void setPlayer(Player& newPlayer);
    void addBullet(Bullet bullet);
    void addEnnemy(Ennemy* e);
    void addObstacle(std::string obstacleTexturePath, int x, int y);
    void addWave(Wave w);

    bool loadNextWave();
    bool isCurrentWaveOver() const;

    std::string getTheme() const;

    void drawObstacles(sf::RenderWindow* window) const;
    void update(sf::RenderWindow* game);

    sf::Sprite getBackground() const;

    sf::FloatRect getCollisionBox() const;

    std::list<Obstacle> getListeObstacles() const;

    bool getGameOver() const;
};



#endif // MAP_HPP_INCLUDED
