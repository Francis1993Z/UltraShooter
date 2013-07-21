#include "WidgetManager.hpp"

WidgetManager::WidgetManager()
{
    //ctor
}

void WidgetManager::setCurrentListeWidgets(std::vector<Button>& listeAdressesButtons){

    delete listeButtons;

    listeButtons = &listeAdressesButtons;
}

void WidgetManager::updatePosSouris(sf::Vector2i posSouris){

    collisionSourisButton(posSouris.x, posSouris.y);
}

void WidgetManager::collisionSourisButton(float x, float y){

    for(unsigned int n=0; n < listeButtons->size(); n++){

        if(listeButtons->at(n).getCollisionBox().contains(x, y)){

            listeButtons->at(n).setSurvolSouris(true);
        }
    }
}

WidgetManager::~WidgetManager()
{
    //dtor
}
