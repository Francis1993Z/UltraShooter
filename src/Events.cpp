#include "Events.hpp"

Events::Events()
{
    //ctor
}

void Events::updateEvents()
{
    if(!Engine::getInstance()->getMenu()->isActif()){

        float x=0.0f;
        float y=0.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            x+=-Engine::getInstance()->getPlayer()->getVitesse();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            x+=Engine::getInstance()->getPlayer()->getVitesse();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            y+=-Engine::getInstance()->getPlayer()->getVitesse();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            y+=Engine::getInstance()->getPlayer()->getVitesse();

        Engine::getInstance()->getPlayer()->move(x, y);

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
