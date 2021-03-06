#ifndef WIDGETMANAGER_INCLUDED_HPP
#define WIDGETMANAGER_INCLUDED_HPP

#include <SFML/Graphics.hpp>

#include "Widget.hpp"
#include "WidgetListener.hpp"

#include <list>

class WidgetManager
{
public:
    WidgetManager();
    void updatePosSouris(float pos_x, float pos_y);
    void positionClicSouris(float pos_x, float pos_y);
    void positionRelachementSouris(float pos_x, float pos_y);
    void setCurrentWidgetListener(WidgetListener* p_widgetListener);
    void collisionSourisButton(float x, float y);
    bool getPause() const;
    void setPause(bool p_pause);
    void codeKeyPressed(int code);
    virtual ~WidgetManager();
protected:
private:
    std::list<Widget *>* listeWidgets;
    Widget* widgetClique;
    bool pause;
    WidgetListener* widgetListener;
};

#endif // WIDGETMANAGER_INCLUDED_HPP
