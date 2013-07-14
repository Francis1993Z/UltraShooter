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

void Map::addSplitter(Splitter newSplitter)
{
    SplitterArray.push_back(newSplitter);
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

        if(Engine::getInstance()->getCollisionManager()->CheckIfOutOfWindow(AllBullets.at(n).getPosition(), 0.0f, 0.0f, 0.0f) == true)
            AllBullets.erase(AllBullets.begin()+n);
    }

///********************************************************************///
///Collision Bullet et Zombie
///********************************************************************///
    for(unsigned int n=0; n < AllBullets.size(); n++)
    {
         for(unsigned int m=0; m < ZombieArray.size(); m++)
    {

          float distance = Distance(AllBullets.at(n).getPosition(), ZombieArray.at(m).getPosition());
          float drbullet =  AllBullets.at(n).getRadius();
          float drennemy =  ZombieArray.at(m).get_dRadius();
          float drbe = drbullet + drennemy;
          float D = distance - drbe;
          if(D<0)
        {
ZombieArray.at(m).takeDamage(AllBullets.at(n).getDamage());
            AllBullets.erase(AllBullets.begin()+n);
            if (ZombieArray.at(m).alive()==false)
            {
            int j=ZombieArray.at(m).getKillPoint();
            player->addPoints(j);
                        ZombieArray.erase(ZombieArray.begin()+m);
            }


  }
    }
}
///********************************************************************///


///********************************************************************///
///Collision Bullet et Splitter et efeft de leur mort
///********************************************************************///
    for(unsigned int n=0; n < AllBullets.size(); n++)
    {
         for(unsigned int m=0; m < SplitterArray.size(); m++)
    {

          float distance = Distance(AllBullets.at(n).getPosition(), SplitterArray.at(m).getPosition());
          float drbullet =  AllBullets.at(n).getRadius();
          float drennemy =  SplitterArray.at(m).get_dRadius();
          float drbe = drbullet + drennemy;
          float D = distance - drbe;
          if(D<0)
        {
SplitterArray.at(m).takeDamage(AllBullets.at(n).getDamage());
            AllBullets.erase(AllBullets.begin()+n);
            if (SplitterArray.at(m).alive()==false)
            {

            int j=SplitterArray.at(m).getKillPoint();
            player->addPoints(j);


float rp = SplitterArray.at(m).getRotation();
float s_distance = SplitterArray.at(m).get_dRadius();
sf::Vector2f base_splitter_pos=SplitterArray.at(m).getPosition();
sf::Vector2f NewSplittersPosition1, NewSplittersPosition2;
///Calcul des positions des deux nouveaux Splitters pour qu'ils soient séparés
  NewSplittersPosition1.x=((cos(rp*M_PI/180)*s_distance))+base_splitter_pos.x;
  NewSplittersPosition1.y=(-(sin(rp*M_PI/180)*s_distance))+base_splitter_pos.y;
  NewSplittersPosition2.x=(cos(rp*M_PI/180)*(-s_distance))+base_splitter_pos.x;
  NewSplittersPosition2.y=-(sin(rp*M_PI/180)*(-s_distance))+base_splitter_pos.y;
unsigned int next_level = SplitterArray.at(m).getNextLevel();

            Map::addSplitter(Splitter(NewSplittersPosition1, *player, next_level));
    Map::addSplitter(Splitter(NewSplittersPosition2, *player, next_level));


                        SplitterArray.erase(SplitterArray.begin()+m);
            }


  }
    }
}
///********************************************************************///
///Répulsion
///********************************************************************///
     for(unsigned int n=0; n < ZombieArray.size(); n++)
    {

     for(unsigned int m=0; m < ZombieArray.size(); m++)
    {
        if(n!=m)
        {
          float distance = Distance(ZombieArray.at(n).getPosition(), ZombieArray.at(m).getPosition());
          float drn =  ZombieArray.at(n).get_dRadius();
          float drm =  ZombieArray.at(m).get_dRadius();
          float drnm = drn + drm;
          float D = distance - drnm;
          if(D<0)
        {
                   float angle = GetAngle(ZombieArray.at(n).getPosition(), ZombieArray.at(m).getPosition());

                   sf::Vector2f fv;
                   sf::Vector2f e_Repulsion;
                   e_Repulsion.x=-8;
                   e_Repulsion.y=-8;
        fv.x=cos(angle) * e_Repulsion.x;
        fv.y=sin(angle) * e_Repulsion.y;

            //ZombieArray.at(n).ApplyForce(-fv.x, -fv.y);
            ZombieArray.at(m).ApplyForce(-fv.x, -fv.y);
            //cout<<"Zombie : "<<m<<" fv.x : "<<fv.x<<" fv.y"<<fv.y<<endl;

        }

        }
    }

    ///fin for Zombie

     for(unsigned int m=0; m < SplitterArray.size(); m++)
    {
        if(n!=m)
        {
          float distance = Distance(ZombieArray.at(n).getPosition(), SplitterArray.at(m).getPosition());
          float drn =  ZombieArray.at(n).get_dRadius();
          float drm =  SplitterArray.at(m).get_dRadius();
          float drnm = drn + drm;
          float D = distance - drnm;
          if(D<0)
        {
                   float angle = GetAngle(ZombieArray.at(n).getPosition(), SplitterArray.at(m).getPosition());

                   sf::Vector2f fv;
                   sf::Vector2f e_Repulsion;
                   e_Repulsion.x=-8;
                   e_Repulsion.y=-8;
        fv.x=cos(angle) * e_Repulsion.x;
        fv.y=sin(angle) * e_Repulsion.y;

            //ZombieArray.at(n).ApplyForce(-fv.x, -fv.y);
            SplitterArray.at(m).ApplyForce(-fv.x, -fv.y);
            //cout<<"Zombie : "<<m<<" fv.x : "<<fv.x<<" fv.y"<<fv.y<<endl;

        }

        }
    }

    }//fin for répulsion zombie


///********************************************************************///


        for(unsigned int n=0; n < ZombieArray.size(); n++)
    {
        ZombieArray.at(n).Update();


        if(Engine::getInstance()->getCollisionManager()->CheckIfOutOfWindow(ZombieArray.at(n).getPosition(), 0.0f, 0.0f, 5.0f) == true)
        {
            ZombieArray.erase(ZombieArray.begin()+n);
        }
    }
            for(unsigned int n=0; n < SplitterArray.size(); n++)
    {
        SplitterArray.at(n).Update();


        if(Engine::getInstance()->getCollisionManager()->CheckIfOutOfWindow(SplitterArray.at(n).getPosition(), 0.0f, 0.0f, 5.0f) == true)
        {
            SplitterArray.erase(SplitterArray.begin()+n);
        }
    }



    for(unsigned int n=0; n < AllBullets.size(); n++)
        game->draw(AllBullets.at(n));
          for(unsigned int n=0; n < ZombieArray.size(); n++)
        game->draw(ZombieArray.at(n));
                  for(unsigned int n=0; n < SplitterArray.size(); n++)
        game->draw(SplitterArray.at(n));
}

Sprite Map::getBackground() const
{
    return background;
}

void Map::setPlayer(Player& newPlayer)
{
player=&newPlayer;
}

sf::FloatRect Map::getCollisionBox() const
{

    return background.getGlobalBounds();
}

std::list <Obstacle> Map::getListeObstacles() const{

    return lObstacles;
}
