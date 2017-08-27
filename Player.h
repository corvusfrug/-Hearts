#ifndef PLAYER_H
#define PLAYER_H

#include "KartGamer.h"

class Player :public KartGamer
{
public:
    Player(string,short int _number);
    Kard* Play(int &iterat, Mast vzM, short int vzNM, int MouseX=0,int MouseY=0);
private:

};

#endif // PLAYER_H
