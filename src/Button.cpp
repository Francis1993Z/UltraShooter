#include "Button.hpp"
#include "Engine.hpp"

#include <iostream>

Button::Button(int p_posX, int p_posY, std::string p_text)
{
    survol = false;

    if (!texture.loadFromFile("ressources/widgets/button.png") || !textureSurvol.loadFromFile("ressources/widgets/buttonSurvol.png") || !textureClic.loadFromFile("ressources/widgets/buttonClic.png")|| !font.loadFromFile("ressources/fonts/arial.ttf"))
    {
        std::cerr << "Erreur lecture fichiers dans button.cpp !" << std::endl;
        exit(10);
    }
    else{

        sprite.setTexture(texture);
        sprite.setPosition(p_posX, p_posY);
        sprite.scale(sf::Vector2f(0.1f, 0.1f));
        text.setString(p_text);
        text.setFont(font);
        text.setCharacterSize(20);
        text.setColor(sf::Color::Red);
        text.setPosition(p_posX+(sprite.getGlobalBounds().width/2)-(text.getGlobalBounds().width/2), p_posY+(sprite.getGlobalBounds().height/2)-(text.getGlobalBounds().height/2));
    }
}

void Button::draw(){

    if(survol){

        sprite.setTexture(textureSurvol);
        sprite.setPosition(0, 0);
        sprite.scale(sf::Vector2f(0.1f, 0.1f));
    }

    //game.draw(sprite);
    //  game.draw(text);
}

sf::FloatRect Button::getCollisionBox() const{

    return sprite.getGlobalBounds();
}

void Button::setSurvolSouris(bool p_survol){

    survol = p_survol;
}

Button::~Button()
{
    //dtor
}
