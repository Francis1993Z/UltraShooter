#include "CollisionManager.hpp"
#include <iostream>

CollisionManager::CollisionManager(Player& p_player, Map& p_gameMap):player(p_player), gameMap(p_gameMap), lObstacles(p_gameMap.getListeObstacles())
{

}

bool CollisionManager::CollisionJoueur(float x, float y){

    collision = false;
    deplacement_x = 0.0f;
    deplacement_y = 0.0f;

    if(CheckIfOutOfWindow(player.getPosition(), x, y, player.getRayon())){

        collision = true;
        CalculDistanceAParcourir(x, y);
    }
    else{

        for(std::list<Obstacle>::const_iterator it = lObstacles.begin(); it != lObstacles.end() && !collision; ++it){

            if(player.getGlobalBounds().intersects(it->getCollisionBox())){

                collision = true;
            }
        }
    }

    return collision;
}

bool CollisionManager::CheckIfOutOfWindow(sf::Vector2f Position, float p_deplacement_x, float p_deplacement_y, float rayon)
{


    if( static_cast<int>(Position.x-rayon) < 0                    ||
            static_cast<unsigned int>(Position.x+rayon) > gameMap.getWidth() ||
            static_cast<int>(Position.y-rayon) < 0                    ||
            static_cast<unsigned int>(Position.y+rayon) > gameMap.getHeight())

        return true;

    else
        return false;
}

void CollisionManager::CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y){

    if(p_deplacement_x>0 && gameMap.getWidth()-player.getPosition().x-p_deplacement_x-player.getRayon() < player.getVitesse())
            deplacement_x=gameMap.getWidth()-(player.getPosition().x-p_deplacement_x)-player.getRayon();
    if(p_deplacement_x<0 && player.getPosition().x-p_deplacement_x-player.getRayon() < player.getVitesse())
            deplacement_x=-(player.getPosition().x-p_deplacement_x)+player.getRayon();
    if(p_deplacement_y>0 && gameMap.getHeight()-player.getPosition().y-p_deplacement_y-player.getRayon() < player.getVitesse())
            deplacement_y=gameMap.getHeight()-(player.getPosition().y-p_deplacement_y)-player.getRayon();
    if(p_deplacement_y<0 && player.getPosition().y-p_deplacement_y-player.getRayon() < player.getVitesse())
            deplacement_y=-(player.getPosition().y-p_deplacement_y)+player.getRayon();

            //std::cout << deplacement_x << std::endl;
}

float CollisionManager::getDeplacementX(){

    return deplacement_x;
}

float CollisionManager::getDeplacementY(){

    return deplacement_y;
}

CollisionManager::~CollisionManager()
{
    //dtor
}
