#include "Menu.hpp"
#include "Engine.hpp"

#include <iostream>
#include "tinyxml.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;

Menu::Menu(sf::Vector2u sizeWindow)
{
    options = false;
    sprite.setTexture(*(Engine::getInstance()->getLoadFiles()->getImgBackgroundMenu()));
    sprite.scale(sf::Vector2f(sizeWindow.x/((float)sprite.getTexture()->getSize().x), sizeWindow.y/((float)sprite.getTexture()->getSize().y)));
    addWidget(new Button(0, 0, "Jouer", 0));
    addWidget(new Button(0, 50, "Scores", 1));
    addWidget(new Button(0, 100, "Quitter", 2));
}

void Menu::draw()
{
    Engine::getInstance()->getRenderWindow()->draw(sprite);

    if(!options){

        drawWidgets();
    }
    else{

        list<Text>::iterator it;

        for(it = listeScores.begin(); it != listeScores.end(); ++it){

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
            break;
        case 1:
            options = true;
            afficherScores();
            break;
        case 2:
            Engine::getInstance()->leaveGame("Quitter Menu");
            break;
        default:
            errorId(idWidgetClique);
            break;
        }
}

bool Menu::isActif() const{

    return actif;
}

void Menu::afficher(){

    actif = true;
}

void Menu::afficherScores(){

    TiXmlDocument doc((getCWD()+"/ressources/saves/scores.xml").c_str());

    if(!doc.LoadFile()){

        cerr << "erreur lors du chargement du fichier scores.xml dans Menu.cpp" << endl;
        cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
        exit(15);
    }
    else{

        TiXmlHandle hdl(&doc);
        TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

        float pos_x = 0.0f;
        float pos_y = 0.0f;
        unsigned int taillePolice = 65;
        int score = 0;
        std::ostringstream oss;

        while (elem){

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
