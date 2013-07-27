#include "Widget.hpp"

Widget::Widget()
{
    type = Basic;
}

int Widget::getId() const
{

    return id;
}

Type Widget::getType() const
{

    return type;
}

Widget::~Widget()
{
    //dtor
}
