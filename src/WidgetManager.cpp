#include "WidgetManager.hpp"
#include "CheckBox.hpp"
#include <iostream>

using namespace std;

WidgetManager::WidgetManager()
{
    pause = true;
}

void WidgetManager::setCurrentWidgetListener(WidgetListener* p_widgetListener)
{

    widgetListener = p_widgetListener;
    listeWidgets = p_widgetListener->getListeWidgets();
}

void WidgetManager::updatePosSouris(float pos_x, float pos_y)
{

    for(list<Widget *>::iterator it = listeWidgets->begin(); it != listeWidgets->end(); ++it)
        {
        if((*it)->getGroup() == widgetListener->getActualGroup()){

            if((*it)->getCollisionBox().contains(pos_x, pos_y))
                {

                    (*it)->setSurvolSouris(true);
                }
            else
                {

                    (*it)->setSurvolSouris(false);
                }
        }
    }
}

void WidgetManager::positionClicSouris(float pos_x, float pos_y)
{

    for(list<Widget *>::iterator it = listeWidgets->begin(); it != listeWidgets->end(); ++it)
        {

    if((*it)->getGroup() == widgetListener->getActualGroup()){

            if((*it)->getCollisionBox().contains(pos_x, pos_y))
                {

                    widgetClique = *it;
                    (*it)->setClicSouris(true);
                }
            else if((*it)->getType() != COCHABLE)
                {

                    (*it)->setClicSouris(false);
                }
        }
    }
}

void WidgetManager::positionRelachementSouris(float pos_x, float pos_y)
{

    for(list<Widget *>::iterator it = listeWidgets->begin(); it != listeWidgets->end(); ++it)
        {

            if((*it)->getGroup() == widgetListener->getActualGroup() && (*it)->getCollisionBox().contains(pos_x, pos_y) && *it == widgetClique)
                {
                    if(widgetClique->getType() == COCHABLE){

                        ((CheckBox*) widgetClique)->setTickedOff(!((CheckBox*) widgetClique)->isTickedOff());
                        cout<<"lol"<<endl;
                    }

                    widgetListener->action(widgetClique);
                    widgetClique = NULL;
                }
        }
}

void WidgetManager::codeKeyPressed(int code)
{

    for(list<Widget *>::iterator it = listeWidgets->begin(); it != listeWidgets->end(); ++it)
        {
            if((*it)->getGroup() == widgetListener->getActualGroup()){

                (*it)->codeKeyPressed(code);
            }
        }
}

bool WidgetManager::getPause() const
{

    return pause;
}

void WidgetManager::setPause(bool p_pause)
{

    pause = p_pause;
}

WidgetManager::~WidgetManager()
{

}
