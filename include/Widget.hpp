#ifndef WIDGET_INCLUDED_HPP
#define WIDGET_INCLUDED_HPP

#include <SFML/Graphics.hpp>

enum Type {Basic};

class Widget
{
public:
    Widget();
    virtual void draw() = 0;
    virtual sf::FloatRect getCollisionBox() const = 0;
    virtual void setSurvolSouris(bool p_survol) = 0;
    virtual void setClicSouris(bool p_clic) = 0;
    virtual void codeKeyPressed(int code) = 0;
    int getId() const;
    Type getType() const;
    virtual ~Widget();
protected:
    int id;
    Type type;
private:
};

#endif // WIDGET_INCLUDED_HPP
