#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "Engine.hpp"

class Map
{
    std::list<Bullet> AllBullets;
    std::list<Entity *> EntityArray;

    std::list<Obstacle> lObstacles;
    std::list<Wave> lWaves;

    std::map<std::string, sf::Texture> mObstacleTextures;

    EnnemyFactory factory;

    int width;
    int height;
    unsigned long ennemies_left;

    sf::Texture backgroundTexture;
    sf::Sprite background;

    std::string theme;

    Entity* EntityTouche;
    Player* localplayer;

    bool gameOver;

public:

    Map(std::string mapPath);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    void setlocalPlayer(Player& newPlayer);
    void addBullet(Bullet bullet);
    void addEnnemy(Ennemy* e);
    void addPlayer(Player* a);
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
