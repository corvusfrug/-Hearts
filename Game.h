#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


#include "Kard.h"
#include "KartGamer.h"
#include "Player.h"
//#include <SDL_mixer.h>

//#using <System.dll>

class Game
{
public:
    Game();
    ~Game();
    void Init();
    bool Intro();
    bool Loop();
    void Outro();
    //void CreateKolod();
private:

    void MixAndDeal();

    Kard* koloda[52];
    KartGamer* gamers[4];

    Kard* vzatka[4];
    short int vzScore;
    short int vzSize;
    short int vzNomMax;
    Mast vzMast;

    int iterat; // Счетчик ходов

    SDL_Window* wnd;
    SDL_Renderer* rnd;
    SDL_Event* evt;
    SDL_Texture* img;



    SDL_Texture* background=NULL;
    SDL_Texture* gamerNorth=NULL;
    SDL_Texture* gamerPlayer=NULL;
    SDL_Texture* gamerWest=NULL;
    SDL_Texture* gamerEast=NULL;

    SDL_Rect bg_rt;
    SDL_Rect bg_g0;
    SDL_Rect bg_g1;
    SDL_Rect bg_g2;
    SDL_Rect bg_g3;
    SDL_Rect bg_imposs;

    TTF_Font *my_font;     //// Шрифт/////

    SDL_Texture* Nadpis1;
    SDL_Texture* Nadpis2;
    SDL_Texture* Nadpis3;
    SDL_Texture* Nadpis4;
    SDL_Texture* Impossible;

    SDL_Texture* Score0;
    SDL_Texture* Score1;
    SDL_Texture* Score2;
    SDL_Texture* Score3;
    SDL_Surface *surfaceMessage; // ТМП-шная "текстура" - поверхность


    //SDL_Surface * sText;
    //SDL_Surface * screen;
    //SDL_Color back_color;

    SDL_Color fore_color;    // ЦВЕТ
    SDL_Color fore_color2;   // ЦВЕТ
    SDL_Rect dest;          // Рект надписи ОЧКОВ


    Mix_Chunk* effectKardDrop;
    Mix_Chunk* effectKardDT;
    Mix_Chunk* effectKardMix;
    Mix_Chunk* effectKardError;
    Mix_Chunk* effectKardQueen;
    Mix_Chunk* effectFinal;
    Mix_Music* music1 = NULL;

    int timerLoop;
    short int activGamer;
    short int startGamer;

    bool EndGameFlag;
    bool flagGP;  // Game-Play Походил ли игрок

    void GeneralEvent();
    void GeneralPrint(bool=false);

};

#endif // GAME_H
