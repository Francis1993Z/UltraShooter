#include "Map.hpp"

using namespace std;
using namespace sf;

Map::Map()
{}

Map::~Map()
{}

void Map::addBullet(Bullet bullet)
{
    AllBullets.push_back(bullet);
}

void Map::update(sf::RenderWindow& game)
{
    Engine* engine = Engine::getInstance();

    for(unsigned int n=0; n < AllBullets.size(); n++)
    {
        AllBullets.at(n).UpdatePosition();

        if(engine->CheckIfOutOfWindow(AllBullets.at(n).getPosition()) == true)
            AllBullets.erase(AllBullets.begin()+n);
    }

    game.clear(Color(255,255,255));

    for(unsigned int n=0; n < AllBullets.size(); n++)
        game.draw(AllBullets.at(n));
}
