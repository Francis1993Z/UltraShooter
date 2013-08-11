#include "Events.hpp"
#include <iostream>

using namespace std;

Events::Events()
{
    //ctor
}

void Events::updateEvents()
{
    if(!Engine::getInstance()->getMenu()->isActif())
        {

            float x=0.0f;
            float y=0.0f;

        DIRECTION left = OFF,
                    right = OFF,
                    up = OFF,
                    down = OFF;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                left=LEFT;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                right = RIGHT;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                up = UP;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                down = DOWN;

        const float speed = Engine::getInstance()->getPlayer()->getSpeed();
        const float diagonale = sqrt(speed*speed/2);
        unsigned int final_direction = (left | right | up | down);
        switch (final_direction)
        {
        case LEFT:
            x-=speed;
            break;

        case RIGHT:
            x+=speed;
            break;

        case UP:
            y-=speed;
            break;

        case DOWN:
            y+=speed;
            break;

        case UP_AND_LEFT:
            y-=diagonale;
            x-=diagonale;
            break;

        case UP_AND_RIGHT:
            y-=diagonale;
            x+=diagonale;
            break;

        case DOWN_AND_LEFT:
            y+=diagonale;
            x-=diagonale;
            break;

        case DOWN_AND_RIGHT:
            y+=diagonale;
            x+=diagonale;
            break;

        default:
            y=0;
            x=0;
            break;
        }

            Engine::getInstance()->getPlayer()->move(x, y);
            Engine::getInstance()->updateView(x,y);

            if(Engine::getInstance()->getCollisionManager()->CollisionJoueur(x, y))
                {
                    Engine::getInstance()->getMusicManager()->playEvent("ressources/sounds/events/impact.ogg");
                    Engine::getInstance()->getPlayer()->move(-x, -y);
                    Engine::getInstance()->getPlayer()->move(Engine::getInstance()->getCollisionManager()->getDeplacementX(), Engine::getInstance()->getCollisionManager()->getDeplacementY());
                }
        }
}

Events::~Events()
{
    //dtor
}
