#include "Menu.hpp"
#include "Engine.hpp"

#include <iostream>
#include "tinyxml.h"

using namespace std;
using namespace sf;

Menu::Menu(sf::Vector2u sizeWindow, View menu_view)
{
    options = false;
    scores = false;
    sf::Vector2f converted_sprite_coord = Engine::getInstance()->getRenderWindow()->mapPixelToCoords(sf::Vector2i(0, 0), menu_view);
    sprite.setPosition(converted_sprite_coord);
    sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgBackgroundMenu()));
    sprite.scale(sf::Vector2f(sizeWindow.x/((float)sprite.getTexture()->getSize().x), sizeWindow.y/((float)sprite.getTexture()->getSize().y)));

    play = new Button(sf::Vector2i(0, 0), "Play", 0, 0);
    scoresB = new Button(sf::Vector2i(0, 50), "High Scores", 1, 0);
    quit = new Button(sf::Vector2i(0, 100), "Quit", 2, 0);
    retourS = new Button(Vector2i(0, sizeWindow.y-50), "Come back", 5, 1);

    play->addLanguage(Fr, "Jouer");
    scoresB->addLanguage(Fr, "Meilleurs Scores");
    quit->addLanguage(Fr, "Quitter");
    retourS->addLanguage(Fr, "Retour");

    addWidget(play);
    addWidget(scoresB);
    addWidget(quit);
    addWidget(new Button(sf::Vector2i(0, 200), "English", 3, 0));
    addWidget(new Button(sf::Vector2i(0, 250), "Français", 4, 0));
    addWidget(retourS);

    setActualGroup(0);
}

void Menu::draw()
{
    if(!options && !scores)
    {

        Engine::getInstance()->getRenderWindow()->draw(sprite);
    }
    else
        {

            list<Text>::iterator it;

            for(it = listeScores.begin(); it != listeScores.end(); ++it)
                {

                    Engine::getInstance()->getRenderWindow()->draw(*it);
                }
        }

        drawWidgets();
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
            scores = true;
            setActualGroup(1);
            afficherScores();
            break;
        case 2:
            Engine::getInstance()->leaveGame("Quitter Menu");
            break;
        case 3:
            play->setCurrentLanguage(En);
            scoresB->setCurrentLanguage(En);
            quit->setCurrentLanguage(En);
            break;
        case 4:
            play->setCurrentLanguage(Fr);
            scoresB->setCurrentLanguage(Fr);
            quit->setCurrentLanguage(Fr);
            break;
        case 5:
            scores = false;
            setActualGroup(0);
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
