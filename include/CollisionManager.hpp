#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED


#include <list>

#include "Player.hpp"
#include "Map.hpp"
#include "Obstacle.hpp"
#include "Zombie.hpp"

class Map;

class CollisionManager
{
public:

    CollisionManager(Player& p_player, Map& p_gameMap);

    bool CollisionJoueur(float x, float y);
    bool CollisionObstacles(sf::FloatRect rect);
    bool CollisionObstacles(int x, int y);
    template<class T> bool Collision(sf::FloatRect rect, TEAM projectile_team,std::vector<T*>& vec);
    bool CollisionEntity(sf::FloatRect rect, TEAM projectile_team, std::vector<Entity *>& EntityArray);
    bool CollisionEnnemy(sf::FloatRect rect, std::vector<Ennemy *>& EnnemyArray);
    bool CollisionPlayer(sf::FloatRect rect, std::vector<Player *>& PlayerArray);
    bool CheckIfOutOfWindow(float pos_x, float pos_y, float rayon);
    bool CollisionContreJoueur(sf::FloatRect rect);

    void update_repulsion(std::vector<Ennemy *>& EnnemyArray);
    void CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y, sf::FloatRect rect);
    void CalculDistanceAParcourirBordMap(float p_deplacement_x, float p_deplacement_y);

    float getDeplacementX();
    float getDeplacementY();

    Entity* getAdresseEntityTouche();

    virtual ~CollisionManager();

protected:
private:

    Player& localplayer;

    Map& gameMap;

    Entity* adresseEntityTouche;

    std::list<Obstacle> lObstacles;

    bool collision;
    bool update_x;
    bool update_y;

    float deplacement_x;
    float deplacement_y;
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
