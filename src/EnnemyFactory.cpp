#include <cstdlib>
#include <ctime>

#include "EnnemyFactory.hpp"
#include "Engine.hpp"

using namespace std;
using namespace sf;

EnnemyFactory::EnnemyFactory()
{
}

void EnnemyFactory::createEnnemies(const string &type, int number) const
{

    Map * gameMap = Engine::getInstance()->getMap();
    CollisionManager * colManager = Engine::getInstance()->getCollisionManager();
    Player *p = Engine::getInstance()->getPlayer();

    int x = p->getOrigin().x;
    int y = p->getOrigin().y;

    int ennemyX;
    int ennemyY;

    bool badCoords = true;

    if(type == "zombie" || type == "splitter")
        {
            while(number > 0)
                {
                    while(badCoords)
                        {
                            ennemyX = rand_a_b(0, gameMap->getWidth());
                            ennemyY = rand_a_b(0, gameMap->getHeight());

                            if(((ennemyX < (x + RAYON) && ennemyX > (x - RAYON)) && (ennemyY < (y + RAYON) && ennemyY > (y - RAYON))) || !colManager->CollisionObstacles(ennemyX, ennemyY))
                                badCoords = true;
                            else
                                badCoords = false;
                        }

                    if(type == "zombie")
                        gameMap->addEnnemy(new Zombie(Vector2f(ennemyX,ennemyY), *p));
                    else
                        gameMap->addEnnemy(new Splitter(Vector2f(ennemyX,ennemyY), *p, 1));

                    --number;
                    badCoords = true;
                }
        }
}
