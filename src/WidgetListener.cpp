#include "WidgetListener.hpp"

#include <iostream>

using namespace std;
using namespace sf;

WidgetListener::WidgetListener()
{

}

void WidgetListener::addWidget(Widget* widget){

    listeWidgets.push_back(widget);
}

void WidgetListener::drawWidgets()
{
    list<Widget *>::iterator it;
    cerr<<"***************"<<endl;

    for(it = listeWidgets.begin(); it != listeWidgets.end(); ++it){
cerr<<"adresse "<<&(*it)<<endl;
        (*it)->draw();
    }

}

list<Widget *>* WidgetListener::getListeWidgets() {

    return &listeWidgets;
}

void WidgetListener::errorId(int id){

    cerr << "ERROR : Id ("<<id<<") du widget est inconnu dans action()" << endl;
    exit(10);
}

WidgetListener::~WidgetListener()
{
    list<Widget *>::iterator it;
cerr<<"-------------------"<<endl;
//cerr<<listeWidgets.size()<<endl;
    for(it = listeWidgets.begin(); it != listeWidgets.end(); ++it){
            cerr<<"adresse "<<&(*it)<<endl;
        delete *it;
    }
}
