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

    Wave w;
    int number;

    while(node)
        {
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
                    cerr << EnnemyTouche->getVie() << endl;
                }
        }


///********************************************************************///
///Répulsion
///********************************************************************///

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

                                    cout << "e_m : " << e_m << endl;

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

    for(unsigned int n=0; n < EnnemyArray.size(); n++)
        {
            if(EnnemyArray.at(n)->getVie() <= 0)
                {

                    int killpoints = EnnemyArray.at(n)->die();
                    player->addPoints(killpoints);
                    EnnemyArray.erase(EnnemyArray.begin()+n);
                }

            else
                {
                    EnnemyArray.at(n)->update();

                    if(Engine::getInstance()->getCollisionManager()->CheckIfOutOfWindow(EnnemyArray.at(n)->getPosition().x, EnnemyArray.at(n)->getPosition().y, 0.0f, 0.0f, 5.0f))
                        EnnemyArray.erase(EnnemyArray.begin()+n);
                }
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
    EnnemyArray.erase(EnnemyArray.begin()+n);
}


sf::FloatRect Map::getCollisionBox() const
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
