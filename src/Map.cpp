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

void Map::update(sf::RenderWindow& game)
{
    Engine* engine = Engine::getInstance();

    for(unsigned int n=0; n < AllBullets.size(); n++)
    {
        AllBullets.at(n).UpdatePosition();

        if(engine->CheckIfOutOfWindow(AllBullets.at(n).getPosition(), 0.0f) == true)
            AllBullets.erase(AllBullets.begin()+n);
    }

        for(unsigned int n=0; n < ZombieArray.size(); n++)
    {
        ZombieArray.at(n).Update();


        if(engine->CheckIfOutOfWindow(ZombieArray.at(n).getPosition(), 5.0f) == true)
        {
            ZombieArray.erase(ZombieArray.begin()+n);
        }
    }

    for(unsigned int n=0; n < AllBullets.size(); n++)
        game.draw(AllBullets.at(n));
          for(unsigned int n=0; n < ZombieArray.size(); n++)
        game.draw(ZombieArray.at(n));
}

Sprite Map::getBackground() const
{
    return background;
}
