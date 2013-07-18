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

Map::Map(std::string mapPath)
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

            std::string path(getCWD() + "/" + elem->Attribute("path"));

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

    for(unsigned int n=0; n < AllBullets.size(); n++)
        {
            AllBullets.at(n).UpdatePosition();

            if(Engine::getInstance()->getCollisionManager()->CheckIfOutOfWindow(AllBullets.at(n).getPosition().x, AllBullets.at(n).getPosition().y, 0.0f, 0.0f, 0.0f) == true)
                AllBullets.erase(AllBullets.begin()+n);
            else if(Engine::getInstance()->getCollisionManager()->CollisionObstacles(AllBullets.at(n).getGlobalBounds()))
                {

                    AllBullets.erase(AllBullets.begin()+n);
                }
            else if(Engine::getInstance()->getCollisionManager()->CollisionEnnemy(AllBullets.at(n).getGlobalBounds(), EnnemyArray))
                {

                    EnnemyTouche = Engine::getInstance()->getCollisionManager()->getAdresseEnnemyTouche();
                    EnnemyTouche->subirDegats(AllBullets.at(n).getDamage());
                }
        }

    Engine::getInstance()->getCollisionManager()->update_repulsion(EnnemyArray);


    for(unsigned int n=0; n < EnnemyArray.size(); n++)
        {
            if(!EnnemyArray.at(n)->alive())
                {
                    player->addPoints(EnnemyArray.at(n)->die());
                    //EnnemyArray.erase(EnnemyArray.begin()+n);
                    deleteEnnemyat(n);
                }

            else
                {
                    EnnemyArray.at(n)->update();

                    if(Engine::getInstance()->getCollisionManager()->CheckIfOutOfWindow(EnnemyArray.at(n)->getPosition().x, EnnemyArray.at(n)->getPosition().y, 0.0f, 0.0f, 5.0f)){

                        EnnemyArray.erase(EnnemyArray.begin()+n);
                    }
                    else if(Engine::getInstance()->getCollisionManager()->CollisionContreJoueur(EnnemyArray.at(n)->getCollisionBox())){

                        player->subirDegats(EnnemyArray.at(n)->getDamage());
                        EnnemyArray.erase(EnnemyArray.begin()+n);
                    }
                }
        }

        if(!player->alive()){

            gameOver = true;
        }

    for(unsigned int n=0; n < AllBullets.size(); n++)
        game->draw(AllBullets.at(n));


    for(unsigned int n=0; n < EnnemyArray.size(); n++)
        game->draw(*EnnemyArray.at(n));
}

Sprite Map::getBackground() const
{
    return background;
}

void Map::setPlayer(Player& newPlayer)
{
    player=&newPlayer;
}

void Map::deleteEnnemyat(unsigned int n)
{
    delete EnnemyArray.at(n);
    EnnemyArray.erase(EnnemyArray.begin()+n);
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

std::list <Obstacle> Map::getListeObstacles() const
{
    return lObstacles;
}

Map::~Map()
{
    for(vector<Ennemy *>::iterator it = EnnemyArray.begin(); it != EnnemyArray.end(); ++it)
        delete *it;
}

bool Map::getGameOver() const{

    return gameOver;
}
