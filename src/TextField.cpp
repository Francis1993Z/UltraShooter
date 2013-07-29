#include "TextField.hpp"
#include "Engine.hpp"
#include "LoadFiles.hpp"

#include <iostream>

using namespace std;
using namespace sf;

TextField::TextField(int p_posX, int p_posY, int p_id)
{
    champs.setSize(sf::Vector2f(270.f, 30.f));
    champs.setFillColor(sf::Color(0, 0, 0));
    champs.setPosition(p_posX, p_posY);
    champs.setOutlineThickness(2);
    champs.setOutlineColor(sf::Color(100, 100, 100));
    contenuChamps.setFont(*(Engine::getInstance()->getLoadFiles()->getPoliceArial()));
    contenuChamps.setColor(sf::Color::Red);
    contenuChamps.setCharacterSize(20);
    contenuChamps.setString("");
    contenuChamps.setPosition(p_posX, p_posY);
}

void TextField::draw()
{

    Engine::getInstance()->getRenderWindow()->draw(champs);
    Engine::getInstance()->getRenderWindow()->draw(contenuChamps);
}

sf::FloatRect TextField::getCollisionBox() const
{

    return champs.getGlobalBounds();
}

void TextField::setSurvolSouris(bool p_survol)
{

}

void TextField::setClicSouris(bool p_clic)
{


}

void TextField::codeKeyPressed(int code)
{

    cout<<code<<endl;

    if(code != 13 && code != 32)
        {

            if(code == 8)
                {

                    str = str.substr(0, str.size()-1);
                }
            else if(str.size() < 15)
                {

                    str+=code;
                }

            contenuChamps.setString(str);
        }
}

string TextField::getText() const{



    return contenuChamps.getString();
}

TextField::~TextField()
{
    //dtor
}
