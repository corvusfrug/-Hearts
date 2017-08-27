#ifndef KARD_H
#define KARD_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

enum Mast
{
    tref=0,
    bubna,
    chervi,
    piki,
    NaM  // Not a Mast
};

class Kard
{
public:
    Kard(
         Mast _mast=piki,
         short int _nominal=12,
         int _posX=10,
         int _posY=10);
    ~Kard();
    void Print(SDL_Texture* img,SDL_Renderer* rnd,int dxPos=0, int dyPos=0, bool avers=false);
    void SetRectPos(double _x=5.0, double _y=3.0);
    void SetKardPos(double _x=5.0, double _y=3.0);

    int GetKardX();
    int GetKardY();
    int GetKardW();
    int GetKardH();

    void SetTuzNom();


    short int GetKardNom();
    Mast GetKardMast();


private:
    int posX;
    int posY;

    Mast mast;
    short int nominal;
    //SDL_Texture* img;
    //SDL_Renderer* rnd;

    SDL_Rect rt1;
    SDL_Rect rt2;
    SDL_Rect rt3;
};


#endif // KARD_H
