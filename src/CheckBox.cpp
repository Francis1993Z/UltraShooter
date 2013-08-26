#include "CheckBox.hpp"
#include "Engine.hpp"

CheckBox::CheckBox(sf::Vector2i p_pos, std::string p_text, int p_group):Widget(p_group)
{
    type = COCHABLE;
    tickedOff = false;

    sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgCheckBox()));
    sf::Vector2f converted_boutton_coord = Engine::getInstance()->getRenderWindow()->mapPixelToCoords(p_pos);
    sprite.setPosition(converted_boutton_coord);
    text.setString(p_text);
    text.setFont(*(Engine::getInstance()->getLoadFiles()->getPoliceArial()));
    text.setCharacterSize(20);
    text.setColor(sf::Color::White);
    text.setPosition(converted_boutton_coord.x+sprite.getGlobalBounds().width +10.0f, converted_boutton_coord.y+(sprite.getGlobalBounds().height/2)-(text.getGlobalBounds().height/2));
}

void CheckBox::draw()
{
    Engine::getInstance()->getRenderWindow()->draw(sprite);
    Engine::getInstance()->getRenderWindow()->draw(text);
}

sf::FloatRect CheckBox::getCollisionBox() const
{
    return sprite.getGlobalBounds();
}

void CheckBox::setSurvolSouris(bool p_survol)
{

}

void CheckBox::setClicSouris(bool p_clic)
{


}

void CheckBox::codeKeyPressed(int code)
{


}

bool CheckBox::isTickedOff() const{

    return tickedOff;
}

void CheckBox::setTickedOff(bool p_tickedOff){

    tickedOff = p_tickedOff;

    if(tickedOff)
        {

            sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgCheckBoxClic()));
        }
    else
        {

            sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgCheckBox()));
        }
}

CheckBox::~CheckBox()
{
    //dtor
}
