#include "Map.hpp"

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
        gameOver=false;
}


int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

void Map::addBullet(Bullet bullet)
{
    AllBullets.push_back(bullet);
}


void Map::addEnnemy(Ennemy* e)
{
    EnnemyArray.push_back(e);
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

void Map::update(RenderWindow* game)
{
    CollisionManager& collisionManager = *Engine::getInstance()->getCollisionManager();

    vector<Bullet>::iterator it = AllBullets.begin();
    vector<Ennemy *>::iterator itEnnemy = EnnemyArray.begin();

    while(it != AllBullets.end())
        {
            it->UpdatePosition();

            if(collisionManager.CheckIfOutOfWindow(it->getPosition().x, it->getPosition().y, 0.0f))
                it = AllBullets.erase(it);
            else if(collisionManager.CollisionObstacles(it->getGlobalBounds()))
                it = AllBullets.erase(it);
            else if(collisionManager.CollisionEnnemy(it->getGlobalBounds(), EnnemyArray))
                {

                    EnnemyTouche = collisionManager.getAdresseEnnemyTouche();
                    EnnemyTouche->subirDegats(it->getDamage());
                it = AllBullets.erase(it);
                }
            else
                ++it;
        }

    Engine::getInstance()->getCollisionManager()->update_repulsion(EnnemyArray);


    while(itEnnemy != EnnemyArray.end())
        {
            if(!(*itEnnemy)->alive())
                {
                    player->addPoints((*itEnnemy)->die());

                    delete *itEnnemy;
                    itEnnemy = EnnemyArray.erase(itEnnemy);
                }
            else
                {
                    (*itEnnemy)->update();

                    if(collisionManager.CheckIfOutOfWindow((*itEnnemy)->getPosition().x, (*itEnnemy)->getPosition().y, 5.0f))
                        {
                            delete *itEnnemy;
                            itEnnemy = EnnemyArray.erase(itEnnemy);
                        }
                    else if(collisionManager.CollisionContreJoueur((*itEnnemy)->getCollisionBox()))
                        {

                            player->subirDegats((*itEnnemy)->getDamage());

                            delete *itEnnemy;
                            itEnnemy = EnnemyArray.erase(itEnnemy);
                        }
                    else
                        ++itEnnemy;
                }
        }

    if(!player->alive())
        gameOver = true;

    for(it = AllBullets.begin(); it != AllBullets.end(); ++it)
        game->draw(*it);


    for(itEnnemy = EnnemyArray.begin(); itEnnemy != EnnemyArray.end(); ++itEnnemy)
        game->draw(*(*itEnnemy));
}

Sprite Map::getBackground() const
{
    return background;
}

void Map::setPlayer(Player& newPlayer)
{
    player=&newPlayer;
}

bool Map::loadNextWave()
{
    if(!lWaves.empty())
        {
            lWaves.front().loadEnnemies(factory);
            lWaves.pop_front();

            return true;
        }

    return false;
}


bool Map::isCurrentWaveOver() const
{
    if(EnnemyArray.empty())
        return true;

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
    for(vector<Ennemy *>::iterator it = EnnemyArray.begin(); it != EnnemyArray.end(); ++it)
        delete *it;
}

bool Map::getGameOver() const
{

    return gameOver;
}
