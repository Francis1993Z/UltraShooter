#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED





#include "Map.hpp"


class Map;

class CollisionManager
{
public:

    CollisionManager(Player& p_player, Map& p_gameMap);

    bool CollisionJoueur(float x, float y);
    bool CollisionObstacles(sf::FloatRect rect);
    bool CollisionObstacles(int x, int y);
    bool CollisionEnnemy(sf::FloatRect rect, std::list<Ennemy *>& EnnemyArray);
    bool CheckIfOutOfWindow(float pos_x, float pos_y, float rayon);
    bool CollisionContreJoueur(sf::FloatRect rect);

    void update_repulsion(std::list<Ennemy *>& EnnemyArray);
    void CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y, sf::FloatRect rect);
    void CalculDistanceAParcourirBordMap(float p_deplacement_x, float p_deplacement_y);

    float getDeplacementX();
    float getDeplacementY();

    Ennemy* getAdresseEnnemyTouche();

    virtual ~CollisionManager();

protected:
private:

    Player& player;

    Map& gameMap;

    Ennemy* adresseEnnemyTouche;

    std::list<Obstacle> lObstacles;

    bool collision;
    bool update_x;
    bool update_y;

    float deplacement_x;
    float deplacement_y;
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
