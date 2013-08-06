#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "Engine.hpp"

class Map
{
    std::list<Projectile *> ProjectilesArray;
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
int tick;
    bool gameOver;

public:

    Map(std::string mapPath);
    ~Map();

    int getWidth() const;
    int getHeight() const;

    void setlocalPlayer(Player& newPlayer);
    void addEnnemy(Ennemy* e);
    void addPlayer(Player* a);
    void addProjectile(Projectile* p);

    //! rmProjectile
    /// cherche un projectile avec l'aide de son adresse
    /// dans la list de projectile et l'enleve.
    void rmProjectile(Projectile* p);

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
