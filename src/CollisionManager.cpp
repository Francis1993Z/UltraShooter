#include "CollisionManager.hpp"
#include <iostream>

inline float Distance(sf::Vector2f o1, sf::Vector2f o2)
{
    float TCoteopposer=o2.y-o1.y;
    float TCoteadjacent=o2.x-o1.x;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);

    return Thypothenuse;
}


inline float GetAngle(sf::Vector2f vec1, sf::Vector2f vec2)
{
    float a=vec2.x-vec1.x;
    float o=vec2.y-vec1.y;
    float angle;

    angle = atan2(-o, a);

    return angle;
}


CollisionManager::CollisionManager(Player& p_player, Map& p_gameMap):player(p_player), gameMap(p_gameMap), lObstacles(p_gameMap.getListeObstacles())
{

}

bool CollisionManager::CollisionJoueur(float x, float y)
{

    collision = false;
    update_x = false;
    update_y = false;
    deplacement_x = 0.0f;
    deplacement_y = 0.0f;

    if(CheckIfOutOfWindow(player.getPosition().x, player.getPosition().y, x, y, player.getRayon()))
        {

            collision = true;
            CalculDistanceAParcourirBordMap(x, y);
        }
    else
        {

            for(std::list<Obstacle>::const_iterator it = lObstacles.begin(); it != lObstacles.end() && !collision; ++it)
                {

                    if(player.getCollisionBox().intersects(it->getCollisionBox()))
                        {

                            collision = true;
                            CalculDistanceAParcourir(x, y, it->getCollisionBox());
                        }
                }
        }

    return collision;
}

bool CollisionManager::CollisionObstacles(sf::FloatRect rect)
{

    collision = false;

    for(std::list<Obstacle>::const_iterator it = lObstacles.begin(); it != lObstacles.end() && !collision; ++it)
        {

            if(rect.intersects(it->getCollisionBox()))
                {

                    collision = true;
                }
        }

    return collision;
}

bool CollisionManager::CollisionEnnemy(sf::FloatRect rect, std::vector<Ennemy *>& EnnemyArray)
{

    collision = false;

    for(unsigned int n=0; n < EnnemyArray.size(); n++)
        {

            if(rect.intersects(EnnemyArray.at(n)->getCollisionBox()))
                {

                    collision = true;
                    adresseEnnemyTouche = &*(EnnemyArray.at(n));//attention
                }
        }

    return collision;
}

bool CollisionManager::CheckIfOutOfWindow(float pos_x, float pos_y, float p_deplacement_x, float p_deplacement_y, float rayon)
{
    if( static_cast<int>(pos_x-rayon) < 0                    ||
            static_cast<unsigned int>(pos_x+rayon) > gameMap.getWidth() ||
            static_cast<int>(pos_y-rayon) < 0                    ||
            static_cast<unsigned int>(pos_y+rayon) > gameMap.getHeight())

        return true;

    else
        return false;
}

void CollisionManager::update_repulsion(std::vector<Ennemy *>& EnnemyArray)
{
    for(unsigned int n=0; n < EnnemyArray.size(); n++)
        {
            for(unsigned int m=0; m < EnnemyArray.size(); m++)
                {
                    if(n != m)
                        {
                            float distance = Distance(EnnemyArray.at(n)->getPosition(), EnnemyArray.at(m)->getPosition());
                            float drn =  EnnemyArray.at(n)->get_dRadius();
                            float drm =  EnnemyArray.at(m)->get_dRadius();
                            float drnm = drn + drm;
                            float D = distance - drnm;

                            if(D < 0)
                                {
                                    float angle = GetAngle(EnnemyArray.at(n)->getPosition(), EnnemyArray.at(m)->getPosition());
                                    float e_m=EnnemyArray.at(n)->getSpeed();

                                    sf::Vector2f fv;
                                    sf::Vector2f e_Repulsion;



                                    e_Repulsion.x=-(e_m/2);
                                    e_Repulsion.y=-(e_m/2);

                                    fv.x=cos(angle) * e_Repulsion.x;
                                    fv.y=sin(angle) * e_Repulsion.y;

                                    //EnnemyArray.at(n).ApplyForce(-fv.x, -fv.y);
                                    EnnemyArray.at(m)->ApplyForce(-fv.x, -fv.y);
                                    //cout<<"Ennemy : "<<m<<" fv.x : "<<fv.x<<" fv.y"<<fv.y<<endl;
                                }
                        }
                }
        }
}

void CollisionManager::CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y, sf::FloatRect rect)
{

    if(p_deplacement_x>0 && rect.left-player.getPosition().x-p_deplacement_x-player.getRayon() < player.getVitesse())
        deplacement_x=rect.left-(player.getPosition().x-p_deplacement_x)-player.getRayon();

    if(p_deplacement_x<0 && player.getPosition().x-p_deplacement_x-player.getRayon()-rect.left-rect.width < player.getVitesse())
        deplacement_x= -(player.getPosition().x-p_deplacement_x-player.getRayon()-rect.left-rect.width);

    if(p_deplacement_y>0 && rect.top -player.getPosition().y-p_deplacement_y-player.getRayon() < player.getVitesse())
        deplacement_y=rect.top-(player.getPosition().y-p_deplacement_y)-player.getRayon();

    if(p_deplacement_y<0 && player.getPosition().y-p_deplacement_y-player.getRayon()-rect.top-rect.height < player.getVitesse())
        deplacement_y= -(player.getPosition().y-p_deplacement_y-player.getRayon()-rect.top-rect.height);

    //std::cout << deplacement_x << std::endl;
}

void CollisionManager::CalculDistanceAParcourirBordMap(float p_deplacement_x, float p_deplacement_y)
{

    if(p_deplacement_x>0 && gameMap.getWidth()-player.getPosition().x-p_deplacement_x-player.getRayon() < player.getVitesse())
        {

            deplacement_x=gameMap.getWidth()-(player.getPosition().x-p_deplacement_x)-player.getRayon();
            update_x=true;
        }
    if(p_deplacement_x<0 && player.getPosition().x-p_deplacement_x-player.getRayon() < player.getVitesse())
        {

            deplacement_x=-(player.getPosition().x-p_deplacement_x)+player.getRayon();
            update_x=true;
        }
    if(p_deplacement_y>0 && gameMap.getHeight()-player.getPosition().y-p_deplacement_y-player.getRayon() < player.getVitesse())
        {

            deplacement_y=gameMap.getHeight()-(player.getPosition().y-p_deplacement_y)-player.getRayon();
            update_y=true;
        }
    if(p_deplacement_y<0 && player.getPosition().y-p_deplacement_y-player.getRayon() < player.getVitesse())
        {

            deplacement_y=-(player.getPosition().y-p_deplacement_y)+player.getRayon();
            update_y=true;
        }

    if(!update_x)
        deplacement_x = p_deplacement_x;

    if(!update_y)
        deplacement_y = p_deplacement_y;
}

float CollisionManager::getDeplacementX()
{

    return deplacement_x;
}

float CollisionManager::getDeplacementY()
{

    return deplacement_y;
}

Ennemy* CollisionManager::getAdresseEnnemyTouche()
{

    return adresseEnnemyTouche;
}

CollisionManager::~CollisionManager()
{
    //dtor
}
