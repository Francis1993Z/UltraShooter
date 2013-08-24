#include "Widget.hpp"

Widget::Widget(int p_group)
{
    type = Basic;
    group = p_group;
}

int Widget::getId() const
{

    return id;
}

Type Widget::getType() const
{

    return type;
}

int Widget::getGroup() const{

    return group;
}

Widget::~Widget()
{
    //dtor
}
