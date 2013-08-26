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

    play = new Button(sf::Vector2i(0, 0), "Play", 0);
    scoresB = new Button(sf::Vector2i(0, 50), "High Scores", 0);
    optionsB = new Button(sf::Vector2i(0, 100), "Option", 0);
    quit = new Button(sf::Vector2i(0, 150), "Quit", 0);
    retourS = new Button(Vector2i(0, sizeWindow.y-50), "Come back", 1);
    musicCB = new CheckBox(sf::Vector2i(0, 0), "Music", 2);
    soundCB = new CheckBox(sf::Vector2i(0, 35), "Sound", 2);
    retourO = new Button(Vector2i(0, sizeWindow.y-50), "Come back", 2);

    addWidget(play);
    addWidget(scoresB);
    addWidget(optionsB);
    addWidget(quit);
    addWidget(retourS);
    addWidget(retourO);
    addWidget(musicCB);
    addWidget(soundCB);

    setActualGroup(0);
}

void Menu::draw()
{
    if(!options && !scores)
    {

        Engine::getInstance()->getRenderWindow()->draw(sprite);
    }
    else if(scores)
    {

            list<Text>::iterator it;

            for(it = listeScores.begin(); it != listeScores.end(); ++it)
                {

                    Engine::getInstance()->getRenderWindow()->draw(*it);
                }
    }

        drawWidgets();
}

void Menu::action(Widget* widgetClique)
{
    if(widgetClique == play){

        actif = false;
        Engine::getInstance()->SwitchView();
    }
    else if(widgetClique == scoresB){

        scores = true;
        setActualGroup(1);
        afficherScores();
    }
    else if(widgetClique == optionsB){

        options = true;
        setActualGroup(2);
    }
    else if(widgetClique == quit){

        Engine::getInstance()->leaveGame("Quitter Menu");
    }
    else if(widgetClique == retourS){

        scores = false;
        setActualGroup(0);
    }
    else if(widgetClique == retourO){

        options = false;
        setActualGroup(0);
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
