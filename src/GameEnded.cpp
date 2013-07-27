#include "GameEnded.hpp"
#include "Engine.hpp"

#include <iostream>

using namespace std;


GameEnded::GameEnded()
{
    actif = false;

    fond.setSize(sf::Vector2f(500.f, 300.f));
    fond.setFillColor(sf::Color(255, 255, 255));
    fond.setPosition((Engine::getInstance()->getRenderWindow()->getSize().x/2)-(fond.getSize().x/2), (Engine::getInstance()->getRenderWindow()->getSize().y/2)-(fond.getSize().y/2));

    titre.setFont(*(Engine::getInstance()->getLoadFiles()->getPoliceArial()));
    titre.setColor(sf::Color::Black);
    titre.setCharacterSize(60);

    messageInformatif.setFont(*(Engine::getInstance()->getLoadFiles()->getPoliceArial()));
    messageInformatif.setColor(sf::Color::Black);
    messageInformatif.setCharacterSize(20);
    messageInformatif.setString("Entrez votre pseudo :");
}

void GameEnded::draw()
{

    Engine::getInstance()->getRenderWindow()->draw(fond);
    Engine::getInstance()->getRenderWindow()->draw(titre);
    Engine::getInstance()->getRenderWindow()->draw(messageInformatif);
    drawWidgets();
}

void GameEnded::action(int widgetClique)
{


}

void GameEnded::setActif(bool p_actif, bool gameOver)
{

    actif = p_actif;

    if(actif)
        {

            addWidget(new TextField(fond.getPosition().x+messageInformatif.getGlobalBounds().width+20, fond.getPosition().y+150, 0));
            addWidget(new Button(fond.getPosition().x+(fond.getSize().x/2), fond.getPosition().y+200, "Ok", 1));

            if(gameOver)
                {

                    titre.setString("GAME OVER !");
                }
            else
                {

                    titre.setString("BRAVO !");
                }

            titre.setPosition(fond.getPosition().x+(fond.getSize().x/2)-(titre.getGlobalBounds().width/2), fond.getPosition().y+20);
            messageInformatif.setPosition(fond.getPosition().x+10, fond.getPosition().y+150);
        }
}

bool GameEnded::isActif() const
{

    return actif;
}

GameEnded::~GameEnded()
{
    //dtor
}
