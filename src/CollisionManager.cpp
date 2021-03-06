#include "CollisionManager.hpp"
#include <iostream>
#include <cfloat>

using namespace std;
using namespace sf;

//!
/// Recupere la distance entre deux points.
inline float Distance(Vector2f o1, Vector2f o2)
{
    float TCoteopposer=o2.y-o1.y;
    float TCoteadjacent=o2.x-o1.x;
    float Tracinecarre=pow(TCoteadjacent,2)+pow(TCoteopposer,2);
    float Thypothenuse=sqrt(Tracinecarre);

    return Thypothenuse;
}

//!
/// Recupere l'angle entre deux points.
inline float GetAngle(Vector2f vec1, Vector2f vec2)
{
    float a=vec2.x-vec1.x;
    float o=vec2.y-vec1.y;
    float angle;

    angle = atan2(-o, a);

    return angle;
}

bool CollisionDroite(Vector2f A, Vector2f B, cercle C)
{
    Vector2f u;
    u.x = B.x - A.x;
    u.y = B.y - A.y;
    //cout<<"u.x : "<<u.x<<" u.y : "<<u.y<<endl;
    Vector2f AC;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    //cout<<"AC.x : "<<AC.x<<" AC.y : "<<AC.y<<endl;
    float numerateur = u.x*AC.y - u.y*AC.x;   // norme du vecteur v
    //cout<<"numerateur : "<<numerateur<<endl;
    if (numerateur <0)
        numerateur = -numerateur ;   // valeur absolue ; si c'est négatif, on prend l'opposé.
    float denominateur = sqrt(u.x*u.x + u.y*u.y);  // norme de u
    float CI = numerateur / denominateur;
    //cout<<"CI : "<<CI<<endl;
    if (CI<C.radius)
        return true;
    else
        return false;
}

inline bool CollisionPointCercle(Vector2f A, cercle C)
{
    Vector2f c_p;
    c_p.x = C.x;
    c_p.y = C.y;

    float d = Distance(A, c_p);
    float D = d - C.radius;
    if (D>0) return false;
    else return true;
}

bool CollisionSeg(Vector2f A, Vector2f B, cercle C)
{
    if (CollisionDroite(A,B,C) == false)
        return false;  // si on ne touche pas la droite, on ne touchera jamais le segment
    Vector2f AB,AC,BC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    BC.x = C.x - B.x;
    BC.y = C.y - B.y;
    float pscal1 = AB.x*AC.x + AB.y*AC.y;  // produit scalaire
    float pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y;  // produit scalaire
    if (pscal1>=0 && pscal2>=0)
        {
            return true;   // I entre A et B, ok.
        }

    //dernière possibilité, A ou B dans le cercle
    if (CollisionPointCercle(A,C))
        return true;
    if (CollisionPointCercle(B,C))
        return true;
    return false;
}

inline Vector2f ProjectionI(Vector2f A, Vector2f B, Vector2f C)
{
    Vector2f u,AC;
    u.x = B.x - A.x;
    u.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    float ti = (u.x*AC.x + u.y*AC.y)/(u.x*u.x + u.y*u.y);
    Vector2f I;
    I.x = A.x + ti*u.x;
    I.y = A.y + ti*u.y;
    return I;
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

    if(CheckIfOutOfWindow(player.getPosition().x, player.getPosition().y, player.getCollisionBox().width/2))
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

bool CollisionManager::CollisionObstaclesPoint(sf::FloatRect rect)
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

bool CollisionManager::CollisionObstaclesPoint(int x, int y)
{

    collision = false;

    for(list<Obstacle>::const_iterator it = lObstacles.begin(); it != lObstacles.end() && !collision; ++it)
        if((it->getCollisionBox().contains(x, y)))
            collision = true;

    return collision;
}

bool CollisionManager::Collision(Projectile& proj, list<Entity *>& EntityArray)
{
    collisiontype tmp_ctype=proj.getCollisionType();
    bool col=false;
    switch (tmp_ctype)
        {
        case POINT:
            col = CollisionPoint(proj.getGlobalBounds(), proj.getTeam(), EntityArray);
            break;
        case SEGMENT:
            //cout<<"SEGMENT"<<endl;
            col=CollisionSegment(proj, EntityArray);
            break;
        default:
            break;
        }
    return col;
}

bool CollisionManager::CollisionObstacles(Projectile& proj)
{

    collisiontype tmp_ctype=proj.getCollisionType();
    bool col=false;
    switch (tmp_ctype)
        {
        case POINT:
            col = CollisionObstaclesPoint(proj.getGlobalBounds());
            break;
        case SEGMENT:
            col=false;
            break;
        default:
            break;
        }
    return col;
}

bool CollisionManager::CollisionPoint(FloatRect rect, TEAM projectile_team, list<Entity *>& EntityArray)
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
                            adresseEntityTouche = &*(*it);
                        }
                }
        }


    return collision;
}

bool CollisionManager::CollisionSegment(Projectile& seg, list<Entity *>& EntityArray)
{
    collision = false;
    lp l;
    Vector2f BB_droite;
    for(list<Entity *>::iterator it = EntityArray.begin(); it != EntityArray.end(); ++it)
        {
            TEAM tmpProjectileteam=seg.getTeam();
            TEAM tmpEntityteam=(*it)->getTeam();
            if((tmpProjectileteam & tmpEntityteam) == NO_TEAMS)//On vérifie si c'est un ennemi.
                {
                    Vector2f B_droite;
                    B_droite.y = (cos((seg.getRotation()*M_PI/180)) * 6000.00f)+seg.getPosition().y;
                    B_droite.x = -(sin((seg.getRotation()*M_PI/180)) * 6000.00f)+seg.getPosition().x;
                    BB_droite=B_droite;
                    Vector2f ennemy_position = (*it)->getPosition();
                    float ennemy_dradius = (*it)->get_dRadius();
                    cercle e_cer;
                    e_cer.x = ennemy_position.x;
                    e_cer.y = ennemy_position.y;
                    e_cer.radius = ennemy_dradius;

                    if (CollisionSeg(seg.getPosition(), B_droite, e_cer))
                        {
                            collision = true;
                            l.push_back(make_pair(*it, Distance(seg.getPosition(), (*it)->getPosition())));

                        }
                }
        }
///On choisi la cible la plus près
    float min_distance=FLT_MAX;
    for(lp::iterator it = l.begin(); it != l.end(); ++it)
        {
            if((*it).second<min_distance)
                {
                    min_distance=(*it).second;
                    adresseEntityTouche = &*((*it).first);
                }
        }

    if(collision)//On change la taille du laser
        {
            seg.setI(ProjectionI(seg.getPosition(), BB_droite, adresseEntityTouche->getPosition()));//on détermine le point d'impact
            float new_seg_d = Distance(seg.getPosition(), seg.getI());
            seg.setSize(sf::Vector2f(seg.getSize().x, new_seg_d));

        }
    else
        {
            seg.setSize(sf::Vector2f(seg.getSize().x, 6000.00f));//s'il n'y a pas de collision, on s'assure que la laser ait sa taille normale
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

    if(p_deplacement_x>0 && rect.left-(player.getPosition().x-p_deplacement_x)-player.getCollisionBox().width/2 < player.getSpeed())
        {

            if(p_deplacement_x>0 && rect.left-(player.getPosition().x-p_deplacement_x)-player.getCollisionBox().width/2 >= 0)
                {

                    deplacement_x=rect.left-(player.getPosition().x-p_deplacement_x)-player.getCollisionBox().width/2;
                    update_x=true;
                }
        }
    if(p_deplacement_x<0 && player.getPosition().x-p_deplacement_x-player.getCollisionBox().width/2-rect.left-rect.width < player.getSpeed())
        {

            if(player.getPosition().x-p_deplacement_x-player.getCollisionBox().width/2-rect.left-rect.width >= 0)
                {

                    deplacement_x= -(player.getPosition().x-p_deplacement_x-player.getCollisionBox().width/2-rect.left-rect.width);
                    update_x=true;
                }
        }
    if(p_deplacement_y>0 && rect.top-(player.getPosition().y-p_deplacement_y)-player.getCollisionBox().width/2 < player.getSpeed())
        {

            if(rect.top-(player.getPosition().y-p_deplacement_y)-player.getCollisionBox().width/2 >= 0)
                {

                    deplacement_y=rect.top-(player.getPosition().y-p_deplacement_y)-player.getCollisionBox().width/2;
                    update_y=true;
                }
        }
    if(p_deplacement_y<0 && player.getPosition().y-p_deplacement_y-player.getCollisionBox().width/2-rect.top-rect.height < player.getSpeed())
        {

            if(player.getPosition().y-p_deplacement_y-player.getCollisionBox().width/2-rect.top-rect.height >= 0)
                {

                    deplacement_y= -(player.getPosition().y-p_deplacement_y-player.getCollisionBox().width/2-rect.top-rect.height);
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
    if(p_deplacement_x>0 && gameMap.getWidth()-player.getPosition().x-p_deplacement_x-player.getCollisionBox().width/2 < player.getSpeed())
        {

            deplacement_x=gameMap.getWidth()-(player.getPosition().x-p_deplacement_x)-player.getCollisionBox().width/2;
            update_x=true;
        }
    if(p_deplacement_x<0 && player.getPosition().x-p_deplacement_x-player.getCollisionBox().width/2 < player.getSpeed())
        {

            deplacement_x=-(player.getPosition().x-p_deplacement_x)+player.getCollisionBox().width/2;
            update_x=true;
        }
    if(p_deplacement_y>0 && gameMap.getHeight()-player.getPosition().y-p_deplacement_y-player.getCollisionBox().width/2 < player.getSpeed())
        {

            deplacement_y=gameMap.getHeight()-(player.getPosition().y-p_deplacement_y)-player.getCollisionBox().width/2;
            update_y=true;
        }
    if(p_deplacement_y<0 && player.getPosition().y-p_deplacement_y-player.getCollisionBox().width/2 < player.getSpeed())
        {

            deplacement_y=-(player.getPosition().y-p_deplacement_y)+player.getCollisionBox().width/2;
            update_y=true;
        }

    if(!update_x)
        deplacement_x = p_deplacement_x;

    if(!update_y)
        deplacement_y = p_deplacement_y;
}

void CollisionManager::CollisionBonus(std::list<Bonus *>& lBonus){

    collision = false;

    for(std::list<Bonus *>::const_iterator it = lBonus.begin(); it != lBonus.end() && !collision; ++it)
        {

            if(Engine::getInstance()->getPlayer()->getCollisionBox().intersects((*it)->getGlobalBounds()))
                {

                    collision = true;
                    (*it)->ramasser();
                }
        }
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
