#include "Wave.hpp"

using namespace std;

Wave::Wave()
{
}

Wave::~Wave()
{
}

void Wave::addEnnemy(string type, int number)
{
    wEnnemy e;

    e.type = type;
    e.number = number;

    lEnnemy.push_back(e);
}
