#include "Button.hpp"
#include "Engine.hpp"

#include <iostream>

using namespace std;

Button::Button(sf::Vector2i p_pos, std::string p_text, int p_id)
{
    survol = false;
    id = p_id;

    sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgButton()));
sf::Vector2f converted_boutton_coord = Engine::getInstance()->getRenderWindow()->mapPixelToCoords(p_pos, Engine::getInstance()->getMenuView());
    sprite.setPosition(converted_boutton_coord);
    sprite.scale(sf::Vector2f(0.1f, 0.1f));
    text.setString(p_text);
    text.setFont(*(Engine::getInstance()->getLoadFiles()->getPoliceArial()));
    text.setCharacterSize(20);
    text.setColor(sf::Color::Red);
    text.setPosition(converted_boutton_coord.x+(sprite.getGlobalBounds().width/2)-(text.getGlobalBounds().width/2), converted_boutton_coord.y+(sprite.getGlobalBounds().height/2)-(text.getGlobalBounds().height/2));
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
