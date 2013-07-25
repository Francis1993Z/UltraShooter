#include "Events.hpp"

Events::Events()
{
    //ctor
}

void Events::updateEvents()
{

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
}

Events::~Events()
{
    //dtor
}
