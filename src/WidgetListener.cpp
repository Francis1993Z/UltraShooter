#include "WidgetListener.hpp"
#include <iostream>

WidgetListener::WidgetListener()
{
    //ctor
}

void WidgetListener::addWidget(Button button){

    listeButtons.push_back(button);
}

void WidgetListener::drawWidgets(sf::RenderWindow& game){

    for(unsigned int n=0; n < listeButtons.size(); n++){

        listeButtons.at(n).draw(game);
    }
}

WidgetListener::~WidgetListener()
{

}
