#include "Kard.h"


Kard::Kard(Mast _mast, short int _nominal,int _posX,int _posY)
{
    posX=_posX;
    posY=_posY;
    mast=_mast;
    nominal=_nominal;
    //rnd=_rnd;
    /*img=NULL;
    img=IMG_LoadTexture(rnd,"texture/cartes.bmp");
    if(img==NULL) std::cout << "&&&&&&\n";*/

    //SDL_Rect rt1;
    rt1.x=posX;
    rt1.y=posY;
    rt1.w=90;
    rt1.h=120;

    //SDL_Rect rt2;
    rt2.x=192.3*(nominal);
    rt2.y=279.2*(int)mast;
    rt2.w=192.3;
    rt2.h=279.2;

    //SDL_Rect rt3;
    rt3.x=192.3*2;
    rt3.y=279.2*4;
    rt3.w=192.3;
    rt3.h=279.2;


}

Kard::~Kard(){}
void Kard::SetRectPos(double _x, double _y)
{
     posX=rt2.x=192.3*_x;
     posY=rt2.y=279.2*_y;
}

void Kard::SetKardPos(double _x, double _y)
{
     posX=rt1.x=_x;
     posY=rt1.y=_y;
}

void Kard::Print(SDL_Texture* img,SDL_Renderer* rnd,int dxPos, int dyPos,bool avers)
{
    //avers=true;///
    posX=rt1.x=dxPos;
    posY=rt1.y=dyPos;

    if(avers)
        SDL_RenderCopy(rnd,img,&rt2,&rt1);
    else
        SDL_RenderCopy(rnd,img,&rt3,&rt1);
}

int Kard::GetKardX() {return posX;}
int Kard::GetKardY() {return posY;}
int Kard::GetKardW() {return rt1.w;}
int Kard::GetKardH() {return rt1.h;}
short int Kard::GetKardNom() {return nominal;}
Mast Kard::GetKardMast(){return mast;}

void Kard::SetTuzNom()
{
    if(nominal==0) nominal = 13;
    else if(nominal==13) nominal = 0;
}

/*
    Mast mast;
    short int nominal;
    SDL_Texture* img;
    static SDL_Texture* revImg;
    SDL_Renderer* rnd;
*/
