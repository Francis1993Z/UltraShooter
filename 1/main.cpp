#include "GameEngine.hpp"

using namespace std;
using namespace sf;


int main()
{
GameEngine eng(1024, 768, 32);
int exitcode=eng.Run();
    return exitcode;
}

