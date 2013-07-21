#include "WidgetListener.hpp"

using namespace std;
using namespace sf;

WidgetListener::WidgetListener()
{
    //ctor
}

void WidgetListener::addWidget(Button button){

    listeButtons.push_back(button);
}

void WidgetListener::drawWidgets()
{
    list<Button>::iterator it;

    for(it = listeButtons.begin(); it != listeButtons.end(); ++it)
        it->draw();

}

WidgetListener::~WidgetListener()
{

}
