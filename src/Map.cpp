#include "Map.hpp"

#include <tinyxml.h>

using namespace std;
using namespace sf;

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

    cout<<width<<endl;
    cout<<height<<endl;

    elem = hdl.Child(2).FirstChildElement().Element();

    if(!elem)
    {
        cerr << "Map 01.map corrompue !" << endl;
        exit(2);
    }

    int x = 42, y;
    while(elem)
    {
        elem->QueryIntAttribute("coordX", &x);
        elem->QueryIntAttribute("coordY", &y);
std::string path(getWC()+"path");

        if(x > 0 && x < width && y > 0 && y < height)
            addObstacle(elem->Attribute(path.c_str()), x, y);

        elem = elem->NextSiblingElement(); // iteration
    }

}

Map::~Map()
{}

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
void Map::addZombie(Zombie newZombie)
{
    ZombieArray.push_back(newZombie);
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

void Map::drawObstacles(RenderWindow* window) const
{
    for(list<Obstacle>::const_iterator it = lObstacles.begin(); it != lObstacles.end(); ++it)
        it->draw(window);
}

void Map::update(RenderWindow* game)
{
    Engine* engine = Engine::getInstance();

    for(unsigned int n=0; n < AllBullets.size(); n++)
    {
        AllBullets.at(n).UpdatePosition();

        if(engine->CheckIfOutOfWindow(AllBullets.at(n).getPosition(), 0.0f, 0.0f, 0.0f) == true)
            AllBullets.erase(AllBullets.begin()+n);
    }

        for(unsigned int n=0; n < ZombieArray.size(); n++)
    {
        ZombieArray.at(n).Update();


        if(engine->CheckIfOutOfWindow(ZombieArray.at(n).getPosition(), 0.0f, 0.0f, 5.0f) == true)
        {
            ZombieArray.erase(ZombieArray.begin()+n);
        }
    }

    for(unsigned int n=0; n < AllBullets.size(); n++)
        game->draw(AllBullets.at(n));
          for(unsigned int n=0; n < ZombieArray.size(); n++)
        game->draw(ZombieArray.at(n));
}

Sprite Map::getBackground() const
{
    return background;
}
