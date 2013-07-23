#include "Menu.hpp"
#include "Engine.hpp"

#include <iostream>

using namespace std;

Menu::Menu()
{
    jouer = false;

    sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgBackgroundMenu()));
    sprite.scale(sf::Vector2f(0.7f, 0.65f));
    addWidget(new Button(0, 0, "Jouer", 0));
    addWidget(new Button(0, 50, "Quitter", 1));
}

void Menu::draw(){

    Engine::getInstance()->getRenderWindow()->draw(sprite);
    drawWidgets();
}

void Menu::action(int idWidgetClique){

    switch (idWidgetClique){

    case 0:
        jouer = true;
        break;
    case 1:
        Engine::getInstance()->leaveGame("Quitter Menu");
        break;
    default:
        errorId(idWidgetClique);
        break;
    }
}

bool Menu::getJouer() const{

    return jouer;
}

Menu::~Menu()
{
}
