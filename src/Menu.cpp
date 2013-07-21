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
        addWidget(Button(0, 0, "Jouer", 0));
    }
}

void Menu::draw(sf::RenderWindow& game){

    game.draw(sprite);
    drawWidgets(game);
}

bool Menu::getJouer() const{

    return jouer;
}

Menu::~Menu()
{
}
