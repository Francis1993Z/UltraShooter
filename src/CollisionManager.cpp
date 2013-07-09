#include "CollisionManager.hpp"
#include <iostream>

CollisionManager::CollisionManager(Player& p_player, Map& p_gameMap):player(p_player), gameMap(p_gameMap)
{

}

bool CollisionManager::CollisionJoueur(float x, float y){

    collision = false;

    if(CheckIfOutOfWindow(player.getPosition(), x, y, player.getRayon())){

        collision = true;
        CalculDistanceAParcourir(x, y);
    }

    return collision;
}

bool CollisionManager::CheckIfOutOfWindow(sf::Vector2f Position, float p_deplacement_x, float p_deplacement_y, float rayon)
{


    if( static_cast<int>(Position.x+p_deplacement_x-rayon) < 0                    ||
            static_cast<unsigned int>(Position.x+p_deplacement_x+rayon) > gameMap.getWidth() ||
            static_cast<int>(Position.y+p_deplacement_y-rayon) < 0                    ||
            static_cast<unsigned int>(Position.y+p_deplacement_y+rayon) > gameMap.getHeight())

        return true;

    else
        return false;
}

void CollisionManager::CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y){

    if(p_deplacement_x>0 && gameMap.getWidth()-player.getPosition().x-player.getRayon() < 15.0f)
            deplacement_x=gameMap.getWidth()-player.getPosition().x-player.getRayon();
    if(p_deplacement_x<0 && player.getPosition().x-player.getRayon() < 15.0f)
            deplacement_x=-player.getPosition().x+player.getRayon();
    if(p_deplacement_y>0 && gameMap.getHeight()-player.getPosition().y-player.getRayon() < 15.0f)
            deplacement_y=gameMap.getHeight()-player.getPosition().y-player.getRayon();
    if(p_deplacement_y<0 && player.getPosition().y-player.getRayon() < 15.0f)
            deplacement_y=-player.getPosition().y+player.getRayon();

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
