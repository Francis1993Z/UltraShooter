#include "CollisionManager.hpp"
#include <iostream>

using namespace std;
using namespace sf;

inline float Distance(Vector2f o1, Vector2f o2)
{
    float TCoteopposer=o2.y-o1.y;
    float TCoteadjacent=o2.x-o1.x;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);

    return Thypothenuse;
}


inline float GetAngle(Vector2f vec1, Vector2f vec2)
{
    float a=vec2.x-vec1.x;
    float o=vec2.y-vec1.y;
    float angle;

    angle = atan2(-o, a);

    return angle;
}


CollisionManager::CollisionManager(Player& p_player, Map& p_gameMap):player(p_player), gameMap(p_gameMap), lObstacles(p_gameMap.getListeObstacles())
{
//cout<<"collision manager player : "<<&player<<endl;
}

bool CollisionManager::CollisionJoueur(float x, float y)
{
    collision = false;
    update_x = false;
    update_y = false;
    deplacement_x = 0.0f;
    deplacement_y = 0.0f;

    if(CheckIfOutOfWindow(player.getPosition().x, player.getPosition().y, player.getRayon()))
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

bool CollisionManager::CollisionObstacles(int x, int y)
{

    collision = false;

    for(list<Obstacle>::const_iterator it = lObstacles.begin(); it != lObstacles.end() && !collision; ++it)
        if((it->getCollisionBox().contains(x, y)))
            collision = true;

    return collision;
}

bool CollisionManager::CollisionEnnemy(FloatRect rect, TEAM projectile_team, list<Entity *>& EntityArray)
{

    collision = false;


    for(list<Entity *>::const_iterator it = EntityArray.begin(); it != EntityArray.end(); ++it)
        {
            //if((*it)==&player) cout<<"hello i'm the player"<<endl;

            TEAM tmpEntityteam=(*it)->getTeam();
            if((projectile_team & tmpEntityteam) == NO_TEAMS)
                {


                    if(rect.intersects((*it)->getCollisionBox()))
                        {
                            //cout<<"projectile_team = "<<projectile_team<<" tmpEntityteam = "<<tmpEntityteam<<" | "<<projectile_team<<" & "<<tmpEntityteam<<" == "<<(projectile_team & tmpEntityteam)<<endl;

                            collision = true;
                            adresseEntityTouche = &*(*it);//attention
                        }
                }
        }


    return collision;
}

bool  CollisionManager::CollisionContreJoueur(FloatRect rect)
{

    collision = false;

    if(rect.intersects(player.getCollisionBox()))
        collision = true;

    return collision;
}

bool CollisionManager::CheckIfOutOfWindow(float pos_x, float pos_y, float rayon)
{
    if( static_cast<int>(pos_x-rayon) < 0                    ||
            static_cast<unsigned int>(pos_x+rayon) > (unsigned) gameMap.getWidth() ||
            static_cast<int>(pos_y-rayon) < 0                    ||
            static_cast<unsigned int>(pos_y+rayon) > (unsigned) gameMap.getHeight())

        return true;

    else
        return false;
}

void CollisionManager::update_repulsion(list<Entity *>& EntityArray)
{
    for(list<Entity *>::const_iterator it = EntityArray.begin(); it != EntityArray.end(); ++it)
        {
            for(list<Entity *>::const_iterator it2 = EntityArray.begin(); it2 != EntityArray.end(); ++it2)
                {
                    if(it != it2)
                        {
                            //cout<<"it : "<<(*it)<<" it2 : "<<(*it2)<<endl;
                            float distance = Distance((*it)->getPosition(), (*it2)->getPosition());
                            float drn =  (*it)->get_dRadius();
                            float drm =  (*it2)->get_dRadius();
                            float drnm = drn + drm;
                            float D = distance - drnm;

                            if(D < 0)
                                {
                                    float angle = GetAngle((*it)->getPosition(), (*it2)->getPosition());
                                    float e_m=(*it)->getSpeed();

                                    Vector2f fv;
                                    Vector2f e_Repulsion;


                                    e_Repulsion.x=-(e_m/2);
                                    e_Repulsion.y=-(e_m/2);

                                    fv.x=cos(angle) * e_Repulsion.x;
                                    fv.y=sin(angle) * e_Repulsion.y;

                                    (*it2)->ApplyForce(-fv.x, -fv.y);
                                }
                        }
                }
        }
}

void CollisionManager::CalculDistanceAParcourir(float p_deplacement_x, float p_deplacement_y, FloatRect rect)
{

    if(p_deplacement_x>0 && rect.left-(player.getPosition().x-p_deplacement_x)-player.getRayon() < player.getSpeed())
        {

            if(p_deplacement_x>0 && rect.left-(player.getPosition().x-p_deplacement_x)-player.getRayon() >= 0)
                {

                    deplacement_x=rect.left-(player.getPosition().x-p_deplacement_x)-player.getRayon();
                    update_x=true;
                }
        }
    if(p_deplacement_x<0 && player.getPosition().x-p_deplacement_x-player.getRayon()-rect.left-rect.width < player.getSpeed())
        {

            if(player.getPosition().x-p_deplacement_x-player.getRayon()-rect.left-rect.width >= 0)
                {

                    deplacement_x= -(player.getPosition().x-p_deplacement_x-player.getRayon()-rect.left-rect.width);
                    update_x=true;
                }
        }
    if(p_deplacement_y>0 && rect.top-(player.getPosition().y-p_deplacement_y)-player.getRayon() < player.getSpeed())
        {

            if(rect.top-(player.getPosition().y-p_deplacement_y)-player.getRayon() >= 0)
                {

                    deplacement_y=rect.top-(player.getPosition().y-p_deplacement_y)-player.getRayon();
                    update_y=true;
                }
        }
    if(p_deplacement_y<0 && player.getPosition().y-p_deplacement_y-player.getRayon()-rect.top-rect.height < player.getSpeed())
        {

            if(player.getPosition().y-p_deplacement_y-player.getRayon()-rect.top-rect.height >= 0)
                {

                    deplacement_y= -(player.getPosition().y-p_deplacement_y-player.getRayon()-rect.top-rect.height);
                    update_y=true;
                }
        }

    if(p_deplacement_x != 0 && deplacement_x == 0 && update_y)
        {

            update_x = false;
        }

    if(p_deplacement_y != 0 && deplacement_y == 0 && update_x)
        {

            update_y = false;
        }

    if(!update_x)
        {

            deplacement_x =p_deplacement_x;
        }
    if(!update_y)
        {

            deplacement_y =p_deplacement_y;
        }
    //std::cout << deplacement_x << std::endl;
}

void CollisionManager::CalculDistanceAParcourirBordMap(float p_deplacement_x, float p_deplacement_y)
{

    if(p_deplacement_x>0 && gameMap.getWidth()-player.getPosition().x-p_deplacement_x-player.getRayon() < player.getSpeed())
        {

            deplacement_x=gameMap.getWidth()-(player.getPosition().x-p_deplacement_x)-player.getRayon();
            update_x=true;
        }
    if(p_deplacement_x<0 && player.getPosition().x-p_deplacement_x-player.getRayon() < player.getSpeed())
        {

            deplacement_x=-(player.getPosition().x-p_deplacement_x)+player.getRayon();
            update_x=true;
        }
    if(p_deplacement_y>0 && gameMap.getHeight()-player.getPosition().y-p_deplacement_y-player.getRayon() < player.getSpeed())
        {

            deplacement_y=gameMap.getHeight()-(player.getPosition().y-p_deplacement_y)-player.getRayon();
            update_y=true;
        }
    if(p_deplacement_y<0 && player.getPosition().y-p_deplacement_y-player.getRayon() < player.getSpeed())
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

Entity* CollisionManager::getAdresseEntityTouche()
{

    return adresseEntityTouche;
}

CollisionManager::~CollisionManager()
{
    //dtor
}
