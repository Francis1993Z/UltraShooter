#include "Button.hpp"
#include "Engine.hpp"

#include <iostream>

Button::Button(int p_posX, int p_posY, std::string p_text, int p_id)
{
    survol = false;
    id = p_id;

    sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgButton()));
    sprite.setPosition(p_posX, p_posY);
    sprite.scale(sf::Vector2f(0.1f, 0.1f));
    text.setString(p_text);
    text.setFont(*(Engine::getInstance()->getLoadFiles()->getPoliceArial()));
    text.setCharacterSize(20);
    text.setColor(sf::Color::Red);
    text.setPosition(p_posX+(sprite.getGlobalBounds().width/2)-(text.getGlobalBounds().width/2), p_posY+(sprite.getGlobalBounds().height/2)-(text.getGlobalBounds().height/2));
}

void Button::draw()
{

    Engine::getInstance()->getRenderWindow()->draw(sprite);
    Engine::getInstance()->getRenderWindow()->draw(text);
}

sf::FloatRect Button::getCollisionBox() const
{

    return sprite.getGlobalBounds();
}

void Button::setSurvolSouris(bool p_survol)
{

    if(p_survol)
        {

            sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgButtonSurvol()));
        }
    else
        {

            sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgButton()));
        }
}

void Button::setClicSouris(bool p_clic)
{

    if(p_clic)
        {

            sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgButtonClic()));
        }
    else
        {

            sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgButton()));
        }
}

void Button::codeKeyPressed(int code)
{


}

Button::~Button()
{
    //dtor
}
