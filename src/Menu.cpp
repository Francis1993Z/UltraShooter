#include "Menu.hpp"
#include "Engine.hpp"

#include <iostream>
#include "tinyxml.h"

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

    listeParticipants[0] = "Francis Marcoux";
    listeParticipants[1] = "Yann Castel";
    listeParticipants[2] = "William Bedu";

    participant.setFont(*(Engine::getInstance()->getLoadFiles()->getPoliceArial()));
    indiceListeParticipants = 0;
    participant.setString(listeParticipants[indiceListeParticipants]);
    charactereSize = 0;
    compteurCharactereSize = 0;
    participant.setCharacterSize(charactereSize);
    participant.setColor(sf::Color::White);
    //pos_x = sizeWindow.x/2;
    //pos_y = sizeWindow.y/2;
    pos_x = 200.0f;
    pos_y = 500.0f;
    rotation = 0.0f;
    participant.setPosition(pos_x, pos_y);
    participant.setOrigin(participant.getGlobalBounds().width/2, participant.getGlobalBounds().height/2);
    pause = 0;
    termine = false;
}

void Menu::draw()
{
    Engine::getInstance()->getRenderWindow()->draw(sprite);

    if(!options)
        {

            drawWidgets();

            if(!termine){

            if(participant.getPosition().x < 500 && participant.getPosition().y  > 200){

                pos_x += 3.0f;
                pos_y -= 3.0f;
                rotation += 360.0f/100.0f;

                ++compteurCharactereSize;

                if(compteurCharactereSize == 2){

                    compteurCharactereSize = 0;
                    ++charactereSize;
                }
            }
            else{

                if(pause != 20){

                   pause++;
                }
                else{

                    ++compteurCharactereSize;

                    if(compteurCharactereSize == 2){

                        compteurCharactereSize = 0;
                        --charactereSize;
                    }

                    if(charactereSize == 0){

                       ++indiceListeParticipants;

                       if(indiceListeParticipants < 3){

                            participant.setString(listeParticipants[indiceListeParticipants]);
                            pos_x = 200.0f;
                            pos_y = 500.0f;
                            rotation = 0.0f;
                            pause = 0;
                            compteurCharactereSize = 0;
                            charactereSize = 0;
                       }
                       else{

                            termine = true;
                        }
                    }
                }
            }

            participant.setPosition(pos_x, pos_y);
            participant.setCharacterSize(charactereSize);
            participant.setRotation(rotation);

            Engine::getInstance()->getRenderWindow()->draw(participant);
            }

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
