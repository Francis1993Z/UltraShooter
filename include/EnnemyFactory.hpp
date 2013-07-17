#ifndef ENNEMYFACTORY_HPP_INCLUDED
#define ENNEMYFACTORY_HPP_INCLUDED

#include <string>

#define RAYON 500

class EnnemyFactory
{

public:

    EnnemyFactory();

    void createEnnemies(const std::string &type, int number) const;
};

#endif // ENNEMYFACTORY_HPP_INCLUDED
