#include "Game.h"
//#include <SDL.h>

int main(int argc, char** argv)
{

    Game G;

    G.Init();
    if(!G.Intro()) {return 0;};
    if(!G.Loop()) {return 0;};
    G.Outro();

    //system("pause");
    return 0;
}
