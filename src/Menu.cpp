#include "Menu.hpp"

#include <iostream>

Menu::Menu()
{
    jouer = true;

    if (!texture.loadFromFile("ressources/backgrounds/menu.png")){

        std::cerr << "Erreur lecture background menu" << std::endl;
        exit(10);
    }
    else{

        sprite.setTexture(texture);
        sprite.scale(sf::Vector2f(0.7f, 0.65f));
        addWidget(Button(0, 0, "Jouer"));
    }
}

void Menu::draw(){
    drawWidgets();
}

bool Menu::getJouer() const{

    return jouer;
}

Menu::~Menu()
{
}
