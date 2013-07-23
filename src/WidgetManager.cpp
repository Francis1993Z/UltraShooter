#include "WidgetManager.hpp"

using namespace std;

WidgetManager::WidgetManager()
{
    pause = true;
}

void WidgetManager::setCurrentWidgetListener(WidgetListener* p_widgetListener){

    widgetListener = p_widgetListener;
    listeButtons = p_widgetListener->getListeWidgets();
}

void WidgetManager::updatePosSouris(float pos_x, float pos_y){

    for(list<Button *>::iterator it = listeButtons->begin(); it != listeButtons->end(); ++it){

        if((*it)->getCollisionBox().contains(pos_x, pos_y)){

            (*it)->setSurvolSouris(true);
        }
        else{

            (*it)->setSurvolSouris(false);
        }
    }
}

void WidgetManager::positionClicSouris(float pos_x, float pos_y){

    for(list<Button *>::iterator it = listeButtons->begin(); it != listeButtons->end(); ++it){

        if((*it)->getCollisionBox().contains(pos_x, pos_y)){

            idWidgetClique = (*it)->getId();
            (*it)->setClicSouris(true);
        }
        else{

            (*it)->setClicSouris(false);
        }
    }
}

void WidgetManager::positionRelachementSouris(float pos_x, float pos_y){

    for(list<Button *>::iterator it = listeButtons->begin(); it != listeButtons->end(); ++it){

        if((*it)->getCollisionBox().contains(pos_x, pos_y) && (*it)->getId() == idWidgetClique){

            widgetListener->action(idWidgetClique);
        }
    }
}

bool WidgetManager::getPause() const{

    return pause;
}

void WidgetManager::setPause(bool p_pause){

    pause = p_pause;
}

WidgetManager::~WidgetManager()
{
    delete widgetListener;
    delete listeButtons;
}
