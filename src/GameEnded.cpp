#include "GameEnded.hpp"
#include "Engine.hpp"

#include <iostream>
#include <string>

#include "tinyxml.h"

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

    switch(widgetClique)
        {

        case 0:
            enregistrerScoreJoueur();
            break;
        case 1:
            break;
        default:
            break;
        }
}

void GameEnded::setActif(bool p_actif, bool gameOver)
{

    actif = p_actif;

    if(actif)
        {

            champsPseudo = new TextField(fond.getPosition().x+messageInformatif.getGlobalBounds().width+20, fond.getPosition().y+150, 1);
            addWidget(champsPseudo);
            addWidget(new Button(fond.getPosition().x+(fond.getSize().x/2), fond.getPosition().y+200, "Ok", 0));

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

void GameEnded::enregistrerScoreJoueur()
{

    bool ajoute = false;

    TiXmlDocument doc((getCWD()+"/ressources/saves/scores.xml").c_str());
    if(champsPseudo->getText() != "" && !doc.LoadFile())
        {

            cerr << "erreur lors du chargement du fichier des scores dans GameEnded.cpp" << endl;
            cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
            exit(15);
        }
    else if(champsPseudo->getText() != "")
        {

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();
            TiXmlElement *elemSelectionne;
            TiXmlElement *f = doc.FirstChildElement();
            long scorePlayer = Engine::getInstance()->getPlayer()->getScore();

            if(!elem)
                {

                    TiXmlElement nouveauPlayer("user");
                    nouveauPlayer.SetAttribute("name", champsPseudo->getText().c_str());
                    nouveauPlayer.SetAttribute("score", scorePlayer);

                    f->InsertEndChild(nouveauPlayer);
                }
            else
                {

                    int scoreEnregistre;
                    int indice = 0;

                    while(elem)
                        {

                            indice++;

                            elem->QueryIntAttribute("score", &scoreEnregistre);

                            if(scoreEnregistre < scorePlayer && !ajoute)
                                {

                                    ajoute = true;
                                    elemSelectionne = elem;
                                }

                            elem = elem->NextSiblingElement();
                        }

                    if(ajoute)
                        {

                            f = doc.FirstChildElement();
                            TiXmlElement nouveauPlayer("user");
                            nouveauPlayer.SetAttribute("name", champsPseudo->getText().c_str());
                            nouveauPlayer.SetAttribute("score", scorePlayer);
                            f->InsertBeforeChild(elemSelectionne, nouveauPlayer);

                            if(indice == 10)
                                {

                                    f->RemoveChild(hdl.FirstChildElement().ChildElement(10).Element());
                                    cerr<<"haha"<<endl;
                                }
                            cerr<<"hehe"<<endl;
                        }
                }

            doc.SaveFile((getCWD()+"/ressources/saves/scores.xml").c_str());
            actif = false;
        }
}

GameEnded::~GameEnded()
{
    //dtor
}
