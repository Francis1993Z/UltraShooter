#include "WidgetListener.hpp"

#include <iostream>

using namespace std;
using namespace sf;

WidgetListener::WidgetListener()
{

}

void WidgetListener::addWidget(Widget* widget)
{

    listeWidgets.push_back(widget);
}

void WidgetListener::drawWidgets()
{
    list<Widget *>::iterator it;

    for(it = listeWidgets.begin(); it != listeWidgets.end(); ++it)
        {

            (*it)->draw();
        }
}

list<Widget *>* WidgetListener::getListeWidgets()
{

    return &listeWidgets;
}

void WidgetListener::errorId(int id)
{

    cerr << "ERROR : Id ("<<id<<") du widget est inconnu dans action()" << endl;
    exit(10);
}

WidgetListener::~WidgetListener()
{
    list<Widget *>::iterator it;

    for(it = listeWidgets.begin(); it != listeWidgets.end(); ++it)
        {

            delete *it;
        }
}
