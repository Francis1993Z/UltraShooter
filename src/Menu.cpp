#include "Menu.hpp"
#include "Engine.hpp"

#include <iostream>
#include "tinyxml.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;

Menu::Menu(sf::Vector2u sizeWindow, View menu_view)
{
    options = false;
    sf::Vector2f converted_sprite_coord = Engine::getInstance()->getRenderWindow()->mapPixelToCoords(sf::Vector2i(0, 0), menu_view);
    sprite.setPosition(converted_sprite_coord);
    sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgBackgroundMenu()));
    sprite.scale(sf::Vector2f(sizeWindow.x/((float)sprite.getTexture()->getSize().x), sizeWindow.y/((float)sprite.getTexture()->getSize().y)));

    play = new Button(sf::Vector2i(0, 0), "Play", 0);
    scores = new Button(sf::Vector2i(0, 50), "High Scores", 1);
    quit = new Button(sf::Vector2i(0, 100), "Quit", 2);

    play->addLanguage(Fr, "Jouer");
    scores->addLanguage(Fr, "Meilleurs Scores");
    quit->addLanguage(Fr, "Quitter");

    addWidget(play);
    addWidget(scores);
    addWidget(quit);
    addWidget(new Button(sf::Vector2i(0, 200), "English", 3));
    addWidget(new Button(sf::Vector2i(0, 250), "Français", 4));
}

void Menu::draw()
{
    Engine::getInstance()->getRenderWindow()->draw(sprite);

    if(!options)
        {

            drawWidgets();
        }
    else
        {

            list<Text>::iterator it;

            for(it = listeScores.begin(); it != listeScores.end(); ++it)
                {

                    Engine::getInstance()->getRenderWindow()->draw(*it);
                }
        }
}

void Menu::action(int idWidgetClique)
{

    switch (idWidgetClique)
        {

        case 0:
            actif = false;
            Engine::getInstance()->SwitchView();
            break;
        case 1:
            options = true;
            afficherScores();
            break;
        case 2:
            Engine::getInstance()->leaveGame("Quitter Menu");
            break;
        case 3:
            play->setCurrentLanguage(En);
            scores->setCurrentLanguage(En);
            quit->setCurrentLanguage(En);
            break;
        case 4:
            play->setCurrentLanguage(Fr);
            scores->setCurrentLanguage(Fr);
            quit->setCurrentLanguage(Fr);
            break;
        default:
            errorId(idWidgetClique);
            break;
        }
}

bool Menu::isActif() const
{

    return actif;
}

void Menu::afficher()
{

    actif = true;
}

void Menu::afficherScores()
{

    TiXmlDocument doc((getCWD()+"/ressources/saves/scores.xml").c_str());

    if(!doc.LoadFile())
        {

            cerr << "erreur lors du chargement du fichier scores.xml dans Menu.cpp" << endl;
            cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
            exit(15);
        }
    else
        {

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            float pos_x = 0.0f;
            float pos_y = 0.0f;
            unsigned int taillePolice = 65;
            int score = 0;
            std::ostringstream oss;

            while (elem)
                {

                    oss.str("");
                    elem->QueryIntAttribute("score", &score);
                    oss << score;
                    Text text(string(elem->Attribute("name"))+" ("+oss.str()+"pts)", *(Engine::getInstance()->getLoadFiles()->getPoliceArial()), taillePolice);
                    text.setPosition(pos_x, pos_y);
                    listeScores.push_back(text);

                    elem = elem->NextSiblingElement();
                    pos_y+=taillePolice;
                    taillePolice-=5;
                }
        }
}

Menu::~Menu()
{
}
