#ifndef COLLISIONMANAGER_HPP_INCLUDED
#define COLLISIONMANAGER_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Map.hpp"
class Map;

class CollisionManager
{
    public:
        CollisionManager(Player& p_player, Map& p_gameMap);
        bool CollisionJoueur(float x, float y);
        bool CheckIfOutOfWindow(sf::Vector2f Position, float deplacement_x, float deplacement_y, float rayon);
        void CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y);
        float getDeplacementX();
        float getDeplacementY();
        virtual ~CollisionManager();
    protected:
    private:
        Player& player;
        Map& gameMap;
        bool collision;
        float deplacement_x;
        float deplacement_y;
};

#endif // COLLISIONMANAGER_HPP_INCLUDED
