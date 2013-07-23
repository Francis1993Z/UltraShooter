#include "WidgetListener.hpp"

#include <iostream>

using namespace std;
using namespace sf;

WidgetListener::WidgetListener()
{

}

void WidgetListener::addWidget(Button* button){

    listeButtons.push_back(button);
}

void WidgetListener::drawWidgets()
{
    list<Button *>::iterator it;

    for(it = listeButtons.begin(); it != listeButtons.end(); ++it)
        (*it)->draw();

}

list<Button *>* WidgetListener::getListeWidgets() {

    return &listeButtons;
}

void WidgetListener::errorId(int id){

    cerr << "ERROR : Id ("<<id<<") du widget est inconnu dans action()" << endl;
    exit(10);
}

WidgetListener::~WidgetListener()
{
    list<Button *>::iterator it;

    for(it = listeButtons.begin(); it != listeButtons.end(); ++it)
        delete *it;
}
