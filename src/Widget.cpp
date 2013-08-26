#include "Widget.hpp"

Widget::Widget(int p_group)
{
    type = Basic;
    group = p_group;
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
