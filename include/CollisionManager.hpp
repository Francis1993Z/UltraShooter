#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include "Map.hpp"

typedef std::list< std::pair<Entity*, float> > lp;

class Map;

class CollisionManager
{
public:

    CollisionManager(Player& p_player, Map& p_gameMap);

    bool CollisionJoueur(float x, float y);
    bool CollisionObstacles(Projectile& proj);
    bool CollisionObstaclesPoint(sf::FloatRect rect);
    bool CollisionObstaclesPoint(int x, int y);
    bool Collision(Projectile& proj, std::list<Entity *>& EntityArray);
    bool CollisionPoint(sf::FloatRect rect, TEAM projectile_team, std::list<Entity *>& EntityArray);
    bool CheckIfOutOfWindow(float pos_x, float pos_y, float rayon);
    bool CollisionContreJoueur(sf::FloatRect rect);
    bool CollisionSegment(Projectile& seg, std::list<Entity *>& EntityArray);
    void update_repulsion(std::list<Entity *>& EntityArray);
    void CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y, sf::FloatRect rect);
    void CalculDistanceAParcourirBordMap(float p_deplacement_x, float p_deplacement_y);
    void CollisionBonus(std::list<Bonus *>& lBonus);

    float getDeplacementX();
    float getDeplacementY();

    Entity* getAdresseEntityTouche();

    virtual ~CollisionManager();

protected:
private:

    Player& player;

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
