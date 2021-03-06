#ifndef WIDGETLISTENER_INCLUDED_HPP
#define WIDGETLISTENER_INCLUDED_HPP

#include <list>

#include "Widget.hpp"

class WidgetListener
{
public:
    WidgetListener();
    std::list<Widget *>* getListeWidgets();
    virtual void action(Widget* widgetClique) = 0;
    virtual void draw() = 0;
    void setActualGroup(int p_id);
    int getActualGroup() const;
    virtual ~WidgetListener();
protected:
    void addWidget(Widget* widget);
    void drawWidgets();
    void errorId(int id);
private:
    std::list<Widget *> listeWidgets;
    int id;
};

#endif // WIDGETLISTENER_INCLUDED_HPP
