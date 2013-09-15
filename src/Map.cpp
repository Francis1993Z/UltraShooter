#include "Map.hpp"
#include <algorithm>
#include <tinyxml.h>

using namespace std;
using namespace sf;

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

Map::Map(string mapPath)
{
    gameOver = false;
    ennemies_left=0;
    string backgroundPath;

    TiXmlDocument doc(mapPath.c_str());

    if(!doc.LoadFile())
        {
            cerr << "Erreur lors du chargement de la Map " << mapPath << endl;
            cerr << "Error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
            exit(1);
        }

    TiXmlHandle hdl(&doc);
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

    if(!elem)
        {
            cerr << "Map 01.map corrompue !" << endl;
            exit(2);
        }

    elem->QueryIntAttribute("width", &width);
    elem->QueryIntAttribute("height", &height);

    elem = elem->NextSiblingElement(); // iteration

    backgroundPath = elem->Attribute("path");

    if (!backgroundTexture.loadFromFile(backgroundPath))
        {
            cerr << "Background " << backgroundPath << " introuvable !" << endl;
            exit(3);
        }
    background.setTexture(backgroundTexture);

    elem = elem->NextSiblingElement(); // iteration

    theme = elem->Attribute("path");

    elem = hdl.Child(2).FirstChildElement().Element();

    if(!elem)
        {
            cerr << "Map 01.map corrompue !" << endl;
            exit(2);
        }

    int x, y;
    while(elem)
        {
            elem->QueryIntAttribute("coordX", &x);
            elem->QueryIntAttribute("coordY", &y);

            string path(getCWD() + "/" + elem->Attribute("path"));

            if(x > 0 && x < width && y > 0 && y < height)
                addObstacle(path.c_str(), x, y);

            elem = elem->NextSiblingElement(); // iteration
        }

    TiXmlNode *node = hdl.Child(3).FirstChild().Node();

    int number;

    while(node)
        {
            Wave w;
            elem = node->FirstChildElement();

            if(!elem)
                {
                    cerr << "Map 01.map corrompue !" << endl;
                    exit(2);
                }

            while(elem)
                {
                    elem->QueryIntAttribute("number", &number);
                    w.addEnnemy(elem->Attribute("type"), number);

                    elem = elem->NextSiblingElement();
                }

            addWave(w);

            node = node->NextSibling(); // iteration
        }
    localplayer = NULL;

}


int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

void Map::addEnnemy(Ennemy* e)
{
    EntityArray.push_back(e);
    ennemies_left++;
}

void Map::addPlayer(Player* a)
{
    //cout<<"player to add : "<<a<<endl;
    EntityArray.push_back(a);
}

void Map::addProjectile(Projectile* p)
{
    ProjectilesArray.push_back(p);
}

void Map::rmProjectile(Projectile* p)
{
    std::list<Projectile *>::iterator findIter = std::find(ProjectilesArray.begin(), ProjectilesArray.end(), p);
    delete *findIter;
    ProjectilesArray.erase(findIter);
}

void Map::addObstacle(std::string obstacleTexturePath, int x, int y)
{
    map<string, Texture>::iterator it = mObstacleTextures.find(obstacleTexturePath);

    if(it != mObstacleTextures.end())
        lObstacles.push_back(Obstacle(&(it->second), x, y));
    else
        {
            Texture obstacleTexture;
            if (!obstacleTexture.loadFromFile(obstacleTexturePath))
                {
                    cerr << "Texture " << obstacleTexturePath << " introuvable !" << endl;
                    exit(4);
                }

            lObstacles.push_back(Obstacle(&(mObstacleTextures.insert(mObstacleTextures.begin(), pair<string, Texture>(obstacleTexturePath, obstacleTexture))->second), x, y));
        }
}

void Map::addWave(Wave w)
{
    lWaves.push_back(w);
}

string Map::getTheme() const
{
    return theme;
}

void Map::drawObstacles(RenderWindow* window) const
{
    for(list<Obstacle>::const_iterator it = lObstacles.begin(); it != lObstacles.end(); ++it)
        it->draw(window);
}

void Map::update()
{
    CollisionManager& collisionManager = *Engine::getInstance()->getCollisionManager();

    list<Projectile *>::iterator it = ProjectilesArray.begin();
    list<Entity *>::iterator itEnnemy = EntityArray.begin();

    while(it != ProjectilesArray.end())
        {
            (*it)->UpdatePosition();

            if(collisionManager.CheckIfOutOfWindow((*it)->getPosition().x, (*it)->getPosition().y, 0))
                {
                    delete *it;
                    it = ProjectilesArray.erase(it);
                }

            else if(collisionManager.CollisionObstacles(*(*it)))
                {
                    delete *it;
                    it = ProjectilesArray.erase(it);
                }

            else if(collisionManager.Collision(*(*it), EntityArray))
                {
                    EntityTouche = collisionManager.getAdresseEntityTouche();
                    EntityTouche->subirDegats((*it)->getDamage());
                    if ((*it)->getCollisionType()==POINT)
                        {
                            delete *it;
                            it = ProjectilesArray.erase(it);

                        }
                    it++;
                }
            else
                ++it;
        }
    localplayer->update();
    Engine::getInstance()->getCollisionManager()->update_repulsion(EntityArray);


    while(itEnnemy != EntityArray.end())
        {

            if((*itEnnemy)!=localplayer)
                {
                    if(!(*itEnnemy)->alive())
                        {
                            localplayer->addPoints((*itEnnemy)->die());
                            lBonus.push_back(((Ennemy*)(*itEnnemy))->getBonus());
                            delete *itEnnemy;
                            itEnnemy = EntityArray.erase(itEnnemy);
                            ennemies_left--;
                        }
                    else
                        {
                            (*itEnnemy)->update();

                            if(collisionManager.CheckIfOutOfWindow((*itEnnemy)->getPosition().x, (*itEnnemy)->getPosition().y, 5.0f))
                                {
                                    delete *itEnnemy;
                                    itEnnemy = EntityArray.erase(itEnnemy);
                                    ennemies_left--;
                                }
                            else if(collisionManager.CollisionContreJoueur((*itEnnemy)->getCollisionBox()))
                                {

                                    localplayer->subirDegats((*itEnnemy)->getDamage());
                                    delete *itEnnemy;
                                    itEnnemy = EntityArray.erase(itEnnemy);
                                    ennemies_left--;
                                }
                            else
                                ++itEnnemy;
                        }

                }
            else
                {

                    ++itEnnemy;
                }


        }

    if(!localplayer->alive()){

        gameOver = true;
    }
    else{

        list<Bonus *>::iterator it = lBonus.begin();

        while(it != lBonus.end())
        {
            collisionManager.CollisionBonus(lBonus);

            if((*it)->isRamasse()){

                delete *it;
                it = lBonus.erase(it);
            }
            else{

                ++it;
            }
        }
    }




}

Sprite Map::getBackground() const
{
    return background;
}

void Map::setlocalPlayer(Player& newPlayer)
{
    if(localplayer == NULL)
        {
            localplayer=&newPlayer;
            addPlayer(localplayer);
        }
    else
        {
            for(list<Entity *>::iterator it = EntityArray.begin(); it != EntityArray.end(); ++it)
                {
                    if ((*it)==localplayer)
                        {
                            delete *it;
                            localplayer=&newPlayer;
                            addPlayer(localplayer);
                        }
                    else
                        {
                            cerr<<"localplayer not found"<<endl;
                        }
                }

        }

}

void Map::drawBonus() const
{

    for(list<Bonus *>::const_iterator it = lBonus.begin(); it != lBonus.end(); ++it)
        Engine::getInstance()->getRenderWindow()->draw(*(*it));
}

bool Map::loadNextWave()
{
    if(!lWaves.empty())
        {
            lWaves.front().loadEnnemies(factory);
            lWaves.pop_front();
            return true;
        }
    else
        {
            return false;
        }

}

void Map::draw(RenderWindow* game)
{
    list<Projectile *>::iterator it = ProjectilesArray.begin();
    list<Entity *>::iterator itEnnemy = EntityArray.begin();

    for(it = ProjectilesArray.begin(); it != ProjectilesArray.end(); ++it)
        game->draw(*(*it));


    for(itEnnemy = EntityArray.begin(); itEnnemy != EntityArray.end(); ++itEnnemy)
        game->draw(*(*itEnnemy));

    for(itEnnemy = EntityArray.begin(); itEnnemy != EntityArray.end(); ++itEnnemy)
        game->draw(*(*itEnnemy));
            drawObstacles(game);//changement à faire
drawBonus();//ici aussi
}

bool Map::isCurrentWaveOver() const
{
    if(ennemies_left==0)
        {
            return true;
        }
    return false;
}

FloatRect Map::getCollisionBox() const
{
    return background.getGlobalBounds();
}

list <Obstacle> Map::getListeObstacles() const
{
    return lObstacles;
}

Map::~Map()
{
    for(list<Entity *>::iterator it = EntityArray.begin(); it != EntityArray.end(); ++it)
        delete *it;
    localplayer = NULL;
}

bool Map::getGameOver() const
{
    return gameOver;
}
