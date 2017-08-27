#include "Game.h"
#include <windows.h>
//#include <iostream>
//#include <SDL.h>
//#include <SDL_mixer.h>
Game::Game()
{
    setlocale(LC_ALL, "Russian"); // delete //
   // koloda[52];
    for(int i=0;i<52;i++)
        koloda[i] = NULL;
    for(int i=0;i<4;i++)
    {
        gamers[i] = NULL;
        vzatka[i] = NULL;
    };

    wnd=NULL;
    rnd=NULL;
    evt=NULL;
    img=NULL;
}

void Game::Init()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    //SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    //Mix_OpenAudio(,,, )
    //Mix_Init(1);
    effectKardDrop = NULL;
    effectKardMix = NULL;
    effectKardError = NULL;
    effectKardDT = NULL;
   // effectKardQueen = NULL;
    effectFinal = NULL;
    music1 = NULL;
    if(
       Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 )==-1
      ) std::cout << "ERROR_AUDIO!\n";

    music1 = Mix_LoadMUS("sound/bg.mp3");
    effectKardDrop = Mix_LoadWAV("sound/drop.wav");
    effectKardMix = Mix_LoadWAV("sound/mix.wav");
    effectKardDT = Mix_LoadWAV("sound/breakKard.wav");
    effectKardError = Mix_LoadWAV("sound/error.wav");
//    effectKardQueen = Mix_LoadWAV("sound/queen.wav");
    effectFinal = Mix_LoadWAV("sound/final.wav");

    if(music1==NULL)  std::cout << "ERROR_AUDIO! BG.mp3\n";
    if(effectKardDrop==NULL)  std::cout << "ERROR_AUDIO! drop.wav\n";
    if(effectKardMix==NULL)  std::cout << "ERROR_AUDIO! mix.wav\n";
    if(effectKardDT==NULL)  std::cout << "ERROR_AUDIO! breakKard.wav\n";
    if(effectKardError==NULL)  std::cout << "ERROR_AUDIO! error.wav\n";
//    if(effectKardQueen==NULL)  std::cout << "ERROR_AUDIO! queen.wav\n";
    if(effectFinal==NULL)  std::cout << "ERROR_AUDIO! final.wav\n";

    //Mix_PlayChannel(-1,effectKardQueen,0);

    wnd = SDL_CreateWindow("CHERVI",
                           100,
                           100,
                           800,
                           600,
                           SDL_WINDOW_SHOWN);
    rnd = SDL_CreateRenderer(wnd,
                             -1,
                             SDL_RENDERER_ACCELERATED);
    evt = new SDL_Event();
    //std::cout << sizeof(wnd) << std::endl;
    //std::cout << sizeof(SDL_Renderer*) << std::endl;
    //std::cout << sizeof(SDL_Event*) << std::endl;
    //std::cout << sizeof(SDL_Texture*) << std::endl;

    /*
    img=NULL;
    img=IMG_LoadTexture(rnd,"texture/cartes.bmp");
    if(img==NULL) std::cout << "&&&&&&\n";*/
    background = IMG_LoadTexture(rnd,"texture/stol.jpg");
    if(background==NULL) std::cout << "!!!!!!!!!!!!!!!!\n";
    gamerNorth  = IMG_LoadTexture(rnd,"texture/1-20.png");
    gamerPlayer = IMG_LoadTexture(rnd,"texture/Avatar.png");
    gamerWest   = IMG_LoadTexture(rnd,"texture/Chief1.png");
    gamerEast   = IMG_LoadTexture(rnd,"texture/Sailor_256.png");
    if(gamerNorth==NULL) std::cout << "gamerNorth!!!!!!\n";
    if(gamerPlayer==NULL) std::cout << "gamerPlayer!!!!!!!!\n";
    if(gamerWest==NULL) std::cout << "gamerWest!!!!!!!!!\n";
    if(gamerEast==NULL) std::cout << "gamerEast!!!!!!\n";

    //std::cout << sizeof(gamerWest) << std::endl;

    img=NULL;
    img=IMG_LoadTexture(rnd,"texture/cartes.png");
    if(img==NULL) std::cout << "&&&&&&\n";

    my_font = TTF_OpenFont("ttf/a_Albionic.ttf", 72); //// dell /////
    //back_color = { 255, 0, 128 };
    fore_color = { 255, 255, 255 };
    fore_color2 = { 0, 0, 0 };

    //setlocale(LC_ALL, "Russian"); // delete //
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(my_font,
                                                       "PLAYER",
                                                       fore_color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    Nadpis1 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "WEST",
                                          fore_color);
    Nadpis2 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "NORTH",
                                          fore_color);
    Nadpis3 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "EAST",
                                          fore_color);
    Nadpis4 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "IMPOSSIBLE!!!",
                                          fore_color2);
    Impossible = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    /*dest.x=500;
    dest.y=500;
    dest.w=100;
    dest.h=50;*/
    //screen = SDL_SetVideoMode(800, 600, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //sdl_setV

    //static SDL_Rect bg_rt;
    //std::cout << sizeof(SDL_Rect) << std::endl;
    bg_rt.x=0;  // Рект фона "background"
    bg_rt.y=0;
    bg_rt.w=800;
    bg_rt.h=600;
    //static SDL_Rect bg_g0;
    //static SDL_Rect bg_g1;
    //static SDL_Rect bg_g2;
    //static SDL_Rect bg_g3;
    bg_g0.w=bg_g0.h=bg_g1.w=bg_g1.h=bg_g2.w=bg_g2.h=bg_g3.w=bg_g3.h=60;

    bg_g0.x=700; // Рект надписи "PLAYER"
    bg_g0.y=500;

    bg_g1.x=10; // Рект надписи "WEST"
    bg_g1.y=460;

    bg_g2.x=110; // Рект надписи "NORTH"
    bg_g2.y=10;

    bg_g3.x=600; // Рект надписи "EAST"
    bg_g3.y=10;


    bg_imposs.x=215; // Рект надписи "IMPOSIBLE!!!"
    bg_imposs.y=240;
    bg_imposs.w=370;
    bg_imposs.h=120;

    //MixAndDeal();
    //std::cout << "NORM!!!\n";
    //MixAndDeal();
    //int j=0;
    gamers[0] = new Player("Player",0);
    gamers[1] = new KartGamer("West",1);
    gamers[2] = new KartGamer("North",2);
    gamers[3] = new KartGamer("East",3);

    MixAndDeal();

    //std::cout << "NORM!!!\n";
    vzSize=0;
    vzScore=0;
    EndGameFlag=false;
    iterat=0; // Счетчик ходов

};

void Game::MixAndDeal()
{
    if(*koloda!=NULL) {Mix_PlayChannel(-1,effectKardMix,0);SDL_Delay(1000);};
    if(*koloda==NULL)
    {
        //std::cout << "NORM111!!!\n";
        srand(time(NULL));
        Mast mTmp=tref;
        int j=0;
        for(int i=0;i<52;i++)
        {
            koloda[i] = new Kard(mTmp,j++);
            //j++;
            if(j==13) {j=0;mTmp=(Mast)((int)mTmp+1);}
            //if(52%4==0) mTmp+1;
        };
    };
   // std::cout << "NORM222!!!\n";
    int n=51,y,i=0;
    Kard* temp;
    while(n-->0)
    {
        temp=koloda[i];
        y=rand()%51;
        koloda[i++]=koloda[y];
        koloda[y]=temp;
        //--n;
    };

    //std::cout << "NORM!!!\n";

    int j=0;
    for(int i=0;i<52;i++)
    {
            gamers[j]->addKard(koloda[i]);
            if((koloda[i]->GetKardNom()==1) && (koloda[i]->GetKardMast()==tref))
            {
                startGamer = activGamer = j;
                vzMast = tref;
                vzNomMax = 1;
            };
            if(i==12||i==25||i==38) j++;
    };
    iterat=0; // Счетчик ходов
    if(activGamer==0) flagGP =false;  // Game-Play Походил ли игрок
}

bool Game::Loop()
{


    while((!EndGameFlag)&&(evt->type!=SDL_QUIT))         // !!!!!!!!!!!!!!LOOP!!!!!!!!!!!!!!!!
    {
            SDL_PollEvent(evt);


            GeneralPrint();


            GeneralEvent();

    };
    if(evt->type==SDL_QUIT)
        return false; else return true;
}

void Game::GeneralEvent()
{
    static bool flagLMD=false; // Left Mouse Down flag
    //static int tmp=0;
    Kard* tmpK;

    static int MouseX = 0;
    static int MouseY = 0;

    if(evt->type==SDL_MOUSEBUTTONDOWN)
    if(evt->button.button == SDL_BUTTON_LEFT)
        flagLMD=true;
    SDL_GetMouseState(&MouseX,&MouseY);
    if(evt->type==SDL_MOUSEBUTTONUP)
        if((evt->button.button == SDL_BUTTON_LEFT)&&(flagLMD))
        flagGP=true;
        if((flagGP))
        {
            if(activGamer!=0) SDL_Delay(1000);
           // if(activGamer==0) flagGP=false;
            //if(tmp==0) // если ход игрока
            //{
                //if(vzSize==0)
            //std::cout << "Err!!\n";
                tmpK=gamers[activGamer++]->Play(iterat,vzMast, vzNomMax, MouseX,MouseY);
                //gamers[2]->SetPlusScore(1);///
                //if(iterat==0) tmpK=NULL;
                //std::cout << "Err2!!\n";
                if(tmpK!=NULL)
                {
                    Mix_PlayChannel(-1,effectKardDrop,0);
                    SDL_Delay(150);
                    iterat++;
                    vzatka[activGamer-1]= tmpK;
   /*МАРШ*/         /*if((tmpK->GetKardMast()==piki)&&(tmpK->GetKardNom()==11))
                    {
                        if(Mix_PlayingMusic()!=0) // Если еще играет
                            if( Mix_PausedMusic() != 1 ) // НЕ На Паузе?
                                {Mix_PauseMusic();SDL_Delay(9500);} ;  // Поставить на паузу
                        Mix_PlayChannel(-1,effectKardQueen,0); // Дама пик
                        GeneralPrint();
                        //SDL_Delay(9500);
                        if(Mix_PlayingMusic()!=0) // Если еще играет
                            if( Mix_PausedMusic() != 1 ) Mix_ResumeMusic();
     /*МАРШ*/       //};
                    if(
                        ((tmpK->GetKardMast()==vzMast)&&
                        (
                          (tmpK->GetKardNom()==0) ||
                          (
                            (tmpK->GetKardNom()>=vzNomMax)&&
                            (vzNomMax!=0)
                          )
                        ))||(vzNomMax==-1)
                      )
                    vzNomMax=tmpK->GetKardNom();
                } else // Если недопустимое действие
                {
                    if(activGamer-1==0) {flagGP=false;flagLMD=false;};
                    activGamer--;
                    if(activGamer<0) activGamer=0;
                    //std::cout << "ERR3" << std::endl;
                    GeneralPrint(true);
                    Mix_PlayChannel(-1,effectKardError,0);
                    SDL_Delay(500);
                    return;
                };
                //vzatka[tmp]->SetRectPos(350,250);
                if((vzatka[activGamer-1]!=NULL)&&
                   (vzatka[activGamer-1]->GetKardMast()==chervi)) vzScore++;
                if((vzatka[activGamer-1]!=NULL)&&
                   (vzatka[activGamer-1]->GetKardMast()==piki) &&
                   (vzatka[activGamer-1]->GetKardNom()==11)) vzScore+=13;/// !!!!! / 26
                if((vzatka[activGamer-1]!=NULL)&&(vzSize==0))
                    vzMast=vzatka[activGamer-1]->GetKardMast();
                vzSize++;

                if(vzSize==4)    // Если взятка разыграна
                {
                    GeneralPrint();
                    SDL_Delay(1000);
                    Mix_PlayChannel(-1,effectKardDT,0);
                    SDL_Delay(500);
                    int tmpNom=startGamer;
                    int tmpMax=0;
                    if(vzatka[startGamer]!=NULL)
                        tmpMax=vzatka[startGamer]->GetKardNom();
                    int tmpj=startGamer;
                    for(int i=0;i<4;i++)
                    {
                        if((vzatka[tmpj]!=NULL)&&
                           (

                             (
                              (vzatka[tmpj]->GetKardNom()==0) //&&   // Если это туз
                              //(vzatka[tmpNom]->GetKardNom()!=0)    // И текущий МАКС не туз
                             ) ||
                            (
                             (vzatka[tmpj]->GetKardNom()>tmpMax)&&   // Или если номинал больше текущего
                             (vzatka[tmpNom]->GetKardNom()!=0)       // И текущий МАКС не туз
                            )
                           )&&
                           (vzatka[tmpj]->GetKardMast()==vzMast))  // И масть совпадает с мастью взятки
                           {
                               tmpNom=tmpj;
                               tmpMax=vzatka[tmpj]->GetKardNom();
                           };
                        (tmpj==3)? tmpj=0 : tmpj++;
                    };
                    gamers[tmpNom]->SetPlusScore(vzScore);

                    vzSize=0;
                    vzScore=0;
                    vzNomMax=-1;
                    vzMast=NaM;
                    for(int i=0;i<4;i++)
                        vzatka[i]=NULL;
                };
                flagLMD=false;
                //if(activGamer==0) flagGP=false;
        };
    if(activGamer==4) activGamer=0;

    if((gamers[0]->GetKolodaSize()==0) &&    // Если все карты вышли
       (gamers[1]->GetKolodaSize()==0) &&
       (gamers[2]->GetKolodaSize()==0) &&
    (gamers[3]->GetKolodaSize()==0)) {SDL_Delay(2000); MixAndDeal();};
    for(int i=0;i<4;i++)
        if(gamers[i]->GetScore()>=100) EndGameFlag=true;
    //flagLMD=false;
    //iterat++;
    if(activGamer==0) flagGP=false;
}

void Game::GeneralPrint(bool impFlag)
{

    SDL_RenderClear(rnd);

    SDL_RenderCopy(rnd,background,NULL,&bg_rt);
    SDL_RenderCopy(rnd,gamerPlayer,NULL,&bg_g0);
    SDL_RenderCopy(rnd,gamerWest,NULL,&bg_g1);
    SDL_RenderCopy(rnd,gamerNorth,NULL,&bg_g2);
    SDL_RenderCopy(rnd,gamerEast,NULL,&bg_g3);
    //std::cout << "NORM!!!\n";
    //K.Print();
    //g1.Print();
    //system("pause");
/////////////////////////////////////////////////////
  //TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

  //SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

  //now you can convert it into a texture

  /*SDL_Rect Message_rect; //create a rect
  Message_rect.x = 200;  //controls the rect's x coordinate
  Message_rect.y = 200; // controls the rect's y coordinte
  Message_rect.w = 800; // controls the width of the rect
  Message_rect.h = 30; // controls the height of the rect*/

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
    dest.x=680; // ИГРОК
    dest.y=450;
    dest.w=100;
    dest.h=30;
    SDL_RenderCopy(rnd, Nadpis1, NULL, &dest); //you put the renderer's name firs

    dest.x=5; // ЗАПАД
    dest.y=570;
    dest.w=85;
    dest.h=30;
    SDL_RenderCopy(rnd, Nadpis2, NULL, &dest);

    dest.x=10; // СЕВЕР
    dest.y=3;
    dest.w=100;
    dest.h=30;
    SDL_RenderCopy(rnd, Nadpis3, NULL, &dest);

    dest.x=680; // ВОСТОК
    dest.y=3;
    dest.w=100;
    dest.h=30;
    SDL_RenderCopy(rnd, Nadpis4, NULL, &dest);



    dest.x=717; // ИГРОК ОЧКИ
    dest.y=510;
    dest.w=30;
    dest.h=50;
    char tmpC[3];
    SDL_itoa(gamers[0]->GetScore(),tmpC,10);
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score0 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_RenderCopy(rnd, Score0, NULL, &dest);
    SDL_DestroyTexture(Score0) ;
    SDL_FreeSurface(surfaceMessage);

    dest.x=30; // ЗАПАД ОЧКИ
    dest.y=520;
    dest.w=30;
    dest.h=50;

    //char tmpC[3];

    SDL_itoa(gamers[1]->GetScore(),tmpC,10);
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score1 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_RenderCopy(rnd, Score1, NULL, &dest);
    SDL_DestroyTexture(Score1) ;
    SDL_FreeSurface(surfaceMessage);

    dest.x=50; // СЕВЕР ОЧКИ
    dest.y=25;
    dest.w=30;
    dest.h=50;
    //char tmpC[3];
    SDL_itoa(gamers[2]->GetScore(),tmpC,10);
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score2 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_RenderCopy(rnd, Score2, NULL, &dest);
    SDL_DestroyTexture(Score2) ;
    SDL_FreeSurface(surfaceMessage);

    dest.x=720; // ВОСТОК ОЧКИ
    dest.y=25;
    dest.w=30;
    dest.h=50;
    //char tmpC[3];
    SDL_itoa(gamers[3]->GetScore(),tmpC,10);
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score3 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_RenderCopy(rnd, Score3, NULL, &dest);
    SDL_DestroyTexture(Score3) ;
    SDL_FreeSurface(surfaceMessage);
    //    TTF_CloseFont(fnt); // Закрываем шрифт
       /* dest.x = 300;
        dest.y = 300;

        //TTF_Font *my_font = NULL; // указатель на шрифт

        //my_font = TTF_OpenFont("ttf/dama_bubey_normal.ttf", 36);




        screen = SDL_CreateRGBSurface(0, 800, 600, 32,
                                       0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
        //screen->w=500;
        //screen->h=500;

        sText = TTF_RenderText_Shaded(my_font, "To be or not to be.", fore_color, back_color);
        SDL_BlitSurface(sText, NULL, screen, &dest);
        //SDL_BlitSurface(sText, NULL, NULL, &dest);
        //SDL_Flip(screen); // отобразим сарфейс screen

        //SDL_Delay(3000); // подождем
        //SDL_BlitSurface()
        SDL_FreeSurface(sText);
        SDL_FreeSurface(screen);*/
///////////////////////////////////////////////////////
    for(int i=0;i<4;i++)
    {
        gamers[i]->Print(img,rnd);
        if(vzatka[i]!=NULL)
            switch(i)
            {
            case 0:
                vzatka[i]->Print(img,rnd,350,310,true);
                break;
            case 1:
                vzatka[i]->Print(img,rnd,200,220,true);
                break;
            case 2:
                vzatka[i]->Print(img,rnd,350,150,true);
                break;
            case 3:
                vzatka[i]->Print(img,rnd,500,220,true);
            break;
            default:
                break;
                //vzatka[i]->Print(img,rnd,200+i*100,220,true);
            };
    };
    if(impFlag)
    {
        //std::cout << "ERR1" << std::endl;
        SDL_RenderCopy(rnd, Impossible, NULL, &bg_imposs);// Надпись "NMPASIBLE"
        //SDL_RenderPresent(rnd);
        //std::cout << "ERR2" << std::endl;
        //SDL_Delay(500);
    }
    SDL_RenderPresent(rnd);
}

bool Game::Intro()
{
    bool EndIntroFlag=false;
    int MouseX_t;
    int MouseY_t;
    static bool flagLMD=false; // Left Mouse Down flag

    setlocale(LC_ALL, "Russian"); // delete //
    SDL_Texture* tt1 = IMG_LoadTexture(rnd, "texture/326411126.png");
    SDL_Event* evtt = new SDL_Event();
    //background = IMG_LoadTexture(rnd,"texture/stol.jpg");
    SDL_Rect tt1r; // Rect БГ Меню
    tt1r.x=30;
    tt1r.y=30;
    tt1r.w=740;
    tt1r.h=540;


    SDL_Rect tt2r; // Rect БГ надпись "CHERVI"
    tt2r.x=200;
    tt2r.y=30;
    tt2r.w=400;
    tt2r.h=80;

    SDL_Texture* tt2;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "CHERVI",
                                          fore_color);
    tt2 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_Texture* tt3;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "START",
                                          fore_color);
    tt3 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_Texture* tt4;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "RULES",
                                          fore_color);
    tt4 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_Texture* tt11;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "MUSIC",
                                          fore_color);
    tt11 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);


    SDL_Rect ttButSta; // кнопка "START"
    ttButSta.x=70;
    ttButSta.y=150;
    ttButSta.w=300;
    ttButSta.h=50;

    SDL_Rect tt4r; // надпись на кнопке "START"
    tt4r.x=110;
    tt4r.y=155;
    tt4r.w=200;
    tt4r.h=40;

    SDL_Rect ttButMus; // кнопка "MUSIC"
    ttButMus.x=70;
    ttButMus.y=300;
    ttButMus.w=300;
    ttButMus.h=50;

    SDL_Rect tt11r; // надпись на кнопке "MUSIC"
    tt11r.x=110;
    tt11r.y=305;
    tt11r.w=200;
    tt11r.h=40;

    SDL_Rect ttButRul; // кнопка "RULES"
    ttButRul.x=70;
    ttButRul.y=450;
    ttButRul.w=300;
    ttButRul.h=50;

    SDL_Rect tt6r; // надпись на кнопке "RULES"
    tt6r.x=110;
    tt6r.y=455;
    tt6r.w=200;
    tt6r.h=40;

    while((!EndIntroFlag)&&(evtt->type!=SDL_QUIT))     // !!!!!!!!!!!!!!LOOP!!!!!!!!!!!!!!!!
    {
        SDL_RenderClear(rnd);
        SDL_RenderCopy(rnd,background,NULL,&bg_rt); // БГ
        SDL_RenderCopy(rnd,tt1,NULL,&tt1r); // БГ Меню

        SDL_RenderCopy(rnd,tt2,NULL,&tt2r); // Надпись "CHERVI"

        SDL_GetMouseState(&MouseX_t,&MouseY_t);

        if(
             (MouseX_t>ttButSta.x) && (MouseX_t<ttButSta.x+ttButSta.w) && // Курсор над кнопкой
             (MouseY_t>ttButSta.y) && (MouseY_t<ttButSta.y+ttButSta.h)
          ) SDL_RenderCopy(rnd,tt1,NULL,&ttButSta); // кнопка "START"
        SDL_RenderCopy(rnd,tt3,NULL,&tt4r); // надпись на кнопке "START"

        if(
             (MouseX_t>ttButMus.x) && (MouseX_t<ttButMus.x+ttButMus.w) && // Курсор над кнопкой
             (MouseY_t>ttButMus.y) && (MouseY_t<ttButMus.y+ttButMus.h)
          )  SDL_RenderCopy(rnd,tt1,NULL,&ttButMus); // кнопка "MUSIC"
        SDL_RenderCopy(rnd,tt11,NULL,&tt11r); // надпись на кнопке "MUSIC"

        if(
             (MouseX_t>ttButRul.x) && (MouseX_t<ttButRul.x+ttButRul.w) && // Курсор над кнопкой
             (MouseY_t>ttButRul.y) && (MouseY_t<ttButRul.y+ttButRul.h)
          )  SDL_RenderCopy(rnd,tt1,NULL,&ttButRul); // кнопка "RULES"
        SDL_RenderCopy(rnd,tt4,NULL,&tt6r); // надпись на кнопке "RULES"



        SDL_PollEvent(evtt);

        if(evtt->type==SDL_MOUSEBUTTONDOWN)
            if(evtt->button.button == SDL_BUTTON_LEFT)
                flagLMD=true;
        SDL_GetMouseState(&MouseX_t,&MouseY_t);
        if(evtt->type==SDL_MOUSEBUTTONUP)
            if((evtt->button.button == SDL_BUTTON_LEFT)&&(flagLMD))
            {
                if(
                    (MouseX_t>ttButSta.x) && (MouseX_t<ttButSta.x+ttButSta.w) && //Нажат СТАРТ
                    (MouseY_t>ttButSta.y) && (MouseY_t<ttButSta.y+ttButSta.h)
                 ) {Mix_PlayChannel(-1,effectKardMix,0); SDL_Delay(1000); EndIntroFlag=true;};

                 if(
                    (MouseX_t>ttButMus.x) && (MouseX_t<ttButMus.x+ttButMus.w) && //Нажата МУЗЫКА
                    (MouseY_t>ttButMus.y) && (MouseY_t<ttButMus.y+ttButMus.h)
                 )
                 {
                     if(Mix_PlayingMusic()==0) // Если еще не играет
                         Mix_PlayMusic(music1,-1);
                     else
                        if( Mix_PausedMusic() == 1 ) // На Паузе?
                            Mix_ResumeMusic();       // Продолжить играть
                        else
                            Mix_PauseMusic();        // Поставить на паузу
                 }

                if(
                    (MouseX_t>ttButRul.x) && (MouseX_t<ttButRul.x+ttButRul.w) && //Нажаты ПРАВИЛА
                    (MouseY_t>ttButRul.y) && (MouseY_t<ttButRul.y+ttButRul.h)
                  )
                  {
                      //Mix_PlayChannel(-1,effectKardDrop,0);
                      system("notepad.exe txt/pr.txt");
                      //std::cout << "Open txt with RULES\n";
                  };
                  flagLMD=false;
            };

        SDL_RenderPresent(rnd);

    };

    //// Distructor
    delete evtt;
    SDL_DestroyTexture(tt1);
    SDL_DestroyTexture(tt2);
    SDL_DestroyTexture(tt3);
    SDL_DestroyTexture(tt4);
    SDL_DestroyTexture(tt11);
    if(EndIntroFlag) return true; else return false;
}

void Game::Outro()
{
    bool EndOutroFlag=false;
    int MouseX_t;
    int MouseY_t;
    static bool flagLMD=false; // Left Mouse Down flag
    char tmpC[3];

    GeneralPrint();

    setlocale(LC_ALL, "Russian"); // delete //
    SDL_Texture* tt1 = IMG_LoadTexture(rnd, "texture/326411126.png");
    SDL_Event* evtt = new SDL_Event();
    //background = IMG_LoadTexture(rnd,"texture/stol.jpg");
    SDL_Rect tt1r;  // Rect bg
    tt1r.x=30;
    tt1r.y=30;
    tt1r.w=740;
    tt1r.h=540;


    SDL_Rect tt2r; // Rect bg"CHERVI"
    tt2r.x=200;
    tt2r.y=30;
    tt2r.w=400;
    tt2r.h=80;


    SDL_Rect ttBestr; // Rect bg "BEST"
    ttBestr.x=520;
    ttBestr.y=170;
    ttBestr.w=100;
    ttBestr.h=50;

    SDL_Texture* tt2;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "CHERVI",
                                          fore_color);
    tt2 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_Texture* tt3;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "QUIT",
                                          fore_color);
    tt3 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_Texture* tt4;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "RESULT",
                                          fore_color);
    tt4 = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    SDL_Texture* ttBest;
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                          "BEST",
                                          fore_color);
    ttBest = SDL_CreateTextureFromSurface(rnd, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);


    SDL_Rect ttButQui; // кнопка "QUIT"
    ttButQui.x=450;
    ttButQui.y=500;
    ttButQui.w=300;
    ttButQui.h=50;

    SDL_Rect tt4r; // надпись на кнопке "START"
    tt4r.x=500;
    tt4r.y=505;
    tt4r.w=200;
    tt4r.h=40;
/*
    SDL_Rect ttButRul; // кнопка ""
    ttButRul.x=70;
    ttButRul.y=450;
    ttButRul.w=300;
    ttButRul.h=50;
*/
    SDL_Rect tt6r; // надпись  "RESULT"
    tt6r.x=250;
    tt6r.y=100;
    tt6r.w=300;
    tt6r.h=40;
///////////////////////////////////////////////////////
    SDL_Rect tt7r; // надпись  "PLAYER"
    tt7r.x=100;
    tt7r.y=200;
    tt7r.w=200;
    tt7r.h=40;

    SDL_Rect tt71r; // Очки  "PLAYER" rect
    tt71r.x=320;
    tt71r.y=200;
    tt71r.w=30;
    tt71r.h=40;

    SDL_itoa(gamers[0]->GetScore(),tmpC,10);
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score0 = SDL_CreateTextureFromSurface(rnd, surfaceMessage); // Очки  "PLAYER" texture
    SDL_FreeSurface(surfaceMessage);

    SDL_Rect tt8r; // надпись  "NORTH"
    tt8r.x=100;
    tt8r.y=250;
    tt8r.w=200;
    tt8r.h=40;

    SDL_Rect tt81r; // Очки  "NORTH" rect
    tt81r.x=320;
    tt81r.y=250;
    tt81r.w=30;
    tt81r.h=40;

    SDL_itoa(gamers[2]->GetScore(),tmpC,10);
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score1 = SDL_CreateTextureFromSurface(rnd, surfaceMessage); // Очки  "NORTH" texture
    SDL_FreeSurface(surfaceMessage);

    SDL_Rect tt9r; // надпись  "EAST"
    tt9r.x=100;
    tt9r.y=300;
    tt9r.w=200;
    tt9r.h=40;

    SDL_Rect tt91r; // Очки  "EAST" rect
    tt91r.x=320;
    tt91r.y=300;
    tt91r.w=30;
    tt91r.h=40;

    SDL_itoa(gamers[3]->GetScore(),tmpC,10);
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score2 = SDL_CreateTextureFromSurface(rnd, surfaceMessage); // Очки  "EAST" texture
    SDL_FreeSurface(surfaceMessage);

    SDL_Rect tt10r; // надпись  "WEST"
    tt10r.x=100;
    tt10r.y=350;
    tt10r.w=200;
    tt10r.h=40;

    SDL_Rect tt101r; // Очки  "WEST" rect
    tt101r.x=320;
    tt101r.y=350;
    tt101r.w=30;
    tt101r.h=40;

    SDL_itoa(gamers[1]->GetScore(),tmpC,10);
    surfaceMessage = TTF_RenderText_Solid(my_font,
                                              tmpC,
                                              fore_color);
    Score3 = SDL_CreateTextureFromSurface(rnd, surfaceMessage); // Очки  "WEST" texture
    SDL_FreeSurface(surfaceMessage);

    SDL_Rect ttBestPlr; // Rect dynamic "BEST"
    ttBestPlr.x=470;
    ttBestPlr.y=250;
    ttBestPlr.w=200;
    ttBestPlr.h=40;

    int tmpBestGamer = 0;
    for(int i=1;i<4;i++)
        if(gamers[i]->GetScore()<gamers[tmpBestGamer]->GetScore()) tmpBestGamer=i;

    if(Mix_PlayingMusic()!=0) // Если еще играет
    if( Mix_PausedMusic() != 1 ) // НЕ На Паузе?
            Mix_PauseMusic();        // Поставить на паузу
                            //Mix_ResumeMusic();       // Продолжить играть
                        //else
                           // Mix_PauseMusic();        // Поставить на паузу

    Mix_PlayChannel(-1,effectFinal,0);


    while((!EndOutroFlag)&&(evtt->type!=SDL_QUIT))     // !!!!!!!!!!!!!!LOOP!!!!!!!!!!!!!!!!
    {
        SDL_RenderClear(rnd);
        SDL_RenderCopy(rnd,background,NULL,&bg_rt); // БГ
        SDL_RenderCopy(rnd,tt1,NULL,&tt1r); // БГ Меню

        SDL_RenderCopy(rnd,tt2,NULL,&tt2r); // Надпись "CHERVI"
        SDL_RenderCopy(rnd,tt4,NULL,&tt6r); // Надпись "RESULT"
        SDL_RenderCopy(rnd,ttBest,NULL,&ttBestr); // Надпись "BEST"

        switch(tmpBestGamer)
        {
        case 0:
            SDL_RenderCopy(rnd,Nadpis1,NULL,&ttBestPlr); // Надпись "PLAYER"
            break;
        case 1:
            SDL_RenderCopy(rnd,Nadpis2,NULL,&ttBestPlr); // Надпись "WEST"
            break;
        case 2:
            SDL_RenderCopy(rnd,Nadpis3,NULL,&ttBestPlr); // Надпись "NORTH"
            break;
        case 3:
            SDL_RenderCopy(rnd,Nadpis4,NULL,&ttBestPlr); // Надпись "EAST"
            break;
        default:
            SDL_RenderCopy(rnd,ttBest,NULL,&ttBestPlr); // Надпись "PLAYER"
        }


        SDL_RenderCopy(rnd,Nadpis1,NULL,&tt7r); // Надпись "PLAYER"
        SDL_RenderCopy(rnd,Score0,NULL,&tt71r); // Очки "PLAYER"

        SDL_RenderCopy(rnd,Nadpis3,NULL,&tt8r); // Надпись "NORTH"
        SDL_RenderCopy(rnd,Score1,NULL,&tt81r); // Очки "NORTH"

        SDL_RenderCopy(rnd,Nadpis4,NULL,&tt9r); // Надпись "EAST"
        SDL_RenderCopy(rnd,Score2,NULL,&tt91r); // Очки "EAST"

        SDL_RenderCopy(rnd,Nadpis2,NULL,&tt10r); // Надпись "WEST"
        SDL_RenderCopy(rnd,Score3,NULL,&tt101r); // Очки "WEST"



        SDL_GetMouseState(&MouseX_t,&MouseY_t);

        if(
             (MouseX_t>ttButQui.x) && (MouseX_t<ttButQui.x+ttButQui.w) && // Курсор над кнопкой
             (MouseY_t>ttButQui.y) && (MouseY_t<ttButQui.y+ttButQui.h)
          ) SDL_RenderCopy(rnd,tt1,NULL,&ttButQui); // кнопка "QUIT"
        SDL_RenderCopy(rnd,tt3,NULL,&tt4r); // надпись на кнопке "QUIT"

        /*if(
             (MouseX_t>ttButRul.x) && (MouseX_t<ttButRul.x+ttButRul.w) && // Курсор над кнопкой
             (MouseY_t>ttButRul.y) && (MouseY_t<ttButRul.y+ttButRul.h)
          )  SDL_RenderCopy(rnd,tt1,NULL,&ttButRul); // кнопка "RULES"
        SDL_RenderCopy(rnd,tt4,NULL,&tt6r); // надпись на кнопке "RULES"*/


        if(Mix_PlayingMusic()!=0)
        if( Mix_PausedMusic() == 1 ) {SDL_RenderPresent(rnd);SDL_Delay(5000);Mix_ResumeMusic();};

        SDL_PollEvent(evtt);

        if(evtt->type==SDL_MOUSEBUTTONDOWN)
            if(evtt->button.button == SDL_BUTTON_LEFT)
                flagLMD=true;
        SDL_GetMouseState(&MouseX_t,&MouseY_t);
        if(evtt->type==SDL_MOUSEBUTTONUP)
            if((evtt->button.button == SDL_BUTTON_LEFT)&&(flagLMD))
            {
                if(
                    (MouseX_t>ttButQui.x) && (MouseX_t<ttButQui.x+ttButQui.w) && //Нажат QUIT
                    (MouseY_t>ttButQui.y) && (MouseY_t<ttButQui.y+ttButQui.h)
                 ) EndOutroFlag=true;
                /*if(
                    (MouseX_t>ttButRul.x) && (MouseX_t<ttButRul.x+ttButRul.w) && //Нажаты ПРАВИЛА
                    (MouseY_t>ttButRul.y) && (MouseY_t<ttButRul.y+ttButRul.h)
                  )
                  {
                      system("notepad.exe txt/pr.txt");
                      //std::cout << "Open txt with RULES\n";
                  };*/
                  flagLMD=false;
            };

        SDL_RenderPresent(rnd);

    };

    //// Distructor
    delete evtt;
    SDL_DestroyTexture(tt1);
    SDL_DestroyTexture(tt2);
    SDL_DestroyTexture(tt3);
    SDL_DestroyTexture(tt4);
    SDL_DestroyTexture(ttBest);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Score0) ;
    SDL_DestroyTexture(Score1) ;
    SDL_DestroyTexture(Score2) ;
    SDL_DestroyTexture(Score3) ;
//    SDL_DestroyTexture(tt4);
    //if(EndIntroFlag) return true; else return false;
}

Game::~Game()
{
    //std::cout << "ERR1!!\n";
    SDL_DestroyRenderer(rnd);
    SDL_DestroyWindow(wnd);
    //std::cout << "ERROR1!!!\n";
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(gamerPlayer);
    SDL_DestroyTexture(gamerWest);
    SDL_DestroyTexture(gamerEast);
    SDL_DestroyTexture(gamerNorth);
    SDL_DestroyTexture(img);

    //std::cout << "ERR2!!\n";
    SDL_DestroyTexture(Nadpis1);
    SDL_DestroyTexture(Nadpis2);
    SDL_DestroyTexture(Nadpis3);
    SDL_DestroyTexture(Nadpis4);
    SDL_DestroyTexture(Impossible) ;

    //std::cout << "ERR21!!\n";
     //std::cout << "ERROR2!!!\n";
    for(int i=0;i<52;i++)
        delete koloda[i];
    //delete[] koloda;

     //std::cout << "ERROR3!!!\n";
    //std::cout << "ERR22!!\n";
    delete gamers[0];
    delete gamers[1];
    delete gamers[2];
    delete gamers[3];

    //std::cout << "ERR23!!\n";
    //delete[] gamers;

    //std::cout << "ERROR4!!!\n";
    for(int i=0;i<4;i++)
        delete vzatka[i];
    //std::cout << "ERR3!!\n";
    delete evt;

    //std::cout << "ERROR3!!!\n";
    TTF_CloseFont(my_font); // Закрываем шрифт
    //std::cout << "ERR4!!\n";
    Mix_HaltMusic();
    Mix_FreeChunk(effectKardDrop);
    Mix_FreeChunk(effectKardMix);
    Mix_FreeChunk(effectKardDT);
    Mix_FreeChunk(effectKardError);
    Mix_FreeChunk(effectKardQueen);
    Mix_FreeChunk(effectFinal);
    Mix_FreeMusic(music1);


    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
