#include "KartGamer.h"

KartGamer::KartGamer(string _name,short int _number)
{
    name=_name;
    number=_number;
    score=0;
    switch(number)
    {
    case 0: // player
        posX=400;
        posY=450;
        break;
    case 1: // West
        posX=10;
        posY=200;
        break;
    case 2: //North
        posX=400;
        posY=10;
        break;
    case 3: // East
        posX=700;
        posY=450;
        break;
    default:
        break;


    };
}
KartGamer::~KartGamer()
{
    //delete gamers[0];
    //std::cout << "ERROR3-1!!!\n";
    //int t=koloda.size();
    /*for(int i=0;i<t;i++)
        {
            std::cout << i << " ERROR3!!!  " << SDL_GetError() << std::endl;
            delete koloda[i];
        };*/
}
void KartGamer::addKard(Kard* k)
{
    koloda.push_back(k);
}
void KartGamer::Print(SDL_Texture* img, SDL_Renderer* rnd)
{
    int step=0;
    int shir=800;
    int vis=600;
    int beg=0;
    if(number!=0) step=20; else  step=40;

    if(number==0||number==2)
        beg = (int) (shir-(90+(step*koloda.size())))/2-45;
    else
        beg = (int) (vis-(120+(step*koloda.size())))/2-60;
    //int step=30;
    //std::cout << koloda.size() << std::endl;
    //system("pause");
    for(int i=0;i<koloda.size();i++)
    {
        if(number==0||number==2)
            if(number==0)
                koloda[i]->Print(img,rnd,beg+=step,posY,true);
            else koloda[i]->Print(img,rnd,beg+=step,posY);
        else
            koloda[i]->Print(img,rnd,posX,beg+=step);
    };
}

Kard* KartGamer::DropKard(int nK)////
{
   // std::cout << koloda.size() << std::endl;
    Kard* result=NULL;
    if(koloda.size()>nK)
        result=koloda[nK];
    else return result;

    int i=nK;
    //Kard* tmp=koloda[i];
    while(i<koloda.size()-1)
        koloda[i]=koloda[++i];
    //koloda[i]=koloda[i]=result;
    koloda.pop_back();
    //std::cout << koloda.size() << std::endl;
    std::cout << "Игрок №" << number << " Очки: " << score << std::endl; // delete //
    return result;
}
Kard* KartGamer::Play(int &iterat, Mast vzM, short int vzNM, int MouseX,int MouseY)
{

    bool mastFlagTmp=false;
    bool mastFlagCherviTmp=false;
    bool mastFlagDamaPikTmp=false;

    int tmpResultKardNom=-1;
    int tmpResultKardNominal=1;

    //std::cout << "ERR 1\n";
    for(int i=0;i<koloda.size();i++)
    {
        if((koloda[i]->GetKardMast()==vzM)|| // Есть ли карты масти старта взятки
           (vzM==NaM))
            {mastFlagTmp=true;} ;

        if((koloda[i]->GetKardMast()==chervi)) // Есть ли Червы
            mastFlagCherviTmp=true;

        if((koloda[i]->GetKardNom()==11)&&
           (koloda[i]->GetKardMast()==piki)) // Есть ли Дама Пик
            mastFlagDamaPikTmp=true;
        if(koloda[i]->GetKardNom()==0) {koloda[i]->SetTuzNom();};
    };
    /*std::cout << "ERR 2\n";
    std::cout << "mastFlagTmp " << mastFlagTmp
              << " | mastFlagCherviTmp " << mastFlagCherviTmp
              << " | mastFlagDamaPikTmp " << mastFlagDamaPikTmp
              << std::endl;*/
    if(iterat==0)
    {
        for(int i=0;i<koloda.size();i++)
            if((koloda[i]->GetKardMast()==vzM)&&(koloda[i]->GetKardNom()==1))
                tmpResultKardNom=i;
        SetTuzNom();
        return DropKard(tmpResultKardNom);
    };
    if(vzM==NaM) // Если АИ задает масть взятки
    {
        tmpResultKardNominal=13;
        for(int i=0;i<koloda.size();i++)
            if(koloda[i]->GetKardNom()<=tmpResultKardNominal)
            {
                tmpResultKardNom=i;
                tmpResultKardNominal=koloda[i]->GetKardNom();
            };
        return DropKard(tmpResultKardNom);
    };

    tmpResultKardNom=-1;
    tmpResultKardNominal=1;
    if(mastFlagTmp) // Если есть карты нужной масти
    {
        //int tmpResultKardNom=-1;
        //int tmpResultKardNominal=1;
        //std::cout << "ERR 3 tmpResultKardNom | " << tmpResultKardNom << std::endl;
        //std::cout << "ERR 3-1 vzNM | " << vzNM << std::endl;
        for(int i=0;i<koloda.size();i++)
        {
            if(
                   (koloda[i]->GetKardMast()==vzM)&&
                   (koloda[i]->GetKardNom()>=tmpResultKardNominal)&&
                   (
                        (koloda[i]->GetKardNom()<vzNM)
                   )//&&
                   //(koloda[i]->GetKardNom()>)
               )

            {
                tmpResultKardNom=i;
                tmpResultKardNominal=koloda[i]->GetKardNom();
            };
        };
        //std::cout << "ERR 4 tmpResultKardNom | " << tmpResultKardNom << std::endl;
        if(tmpResultKardNom==-1)
            for(int i=0;i<koloda.size();i++)
                if((koloda[i]->GetKardMast()==vzM)&&
                   (koloda[i]->GetKardNom()>tmpResultKardNominal)&&
                       !(
                          (koloda[i]->GetKardMast()==piki)&&
                          (koloda[i]->GetKardNom()==11)
                       )
                   )
                {
                    tmpResultKardNom=i;
                    tmpResultKardNominal=koloda[i]->GetKardNom();
                };
        //std::cout << "ERR 4-2 tmpResultKardNom | " << tmpResultKardNom << std::endl;
        if(tmpResultKardNom!=-1)
        {SetTuzNom();return DropKard(tmpResultKardNom);} else return NULL;
    };

    if((!mastFlagTmp)&&(mastFlagDamaPikTmp)) // Кидаем подляну - Даму пик
        for(int i=0;i<koloda.size();i++)
            if((koloda[i]->GetKardNom()==11)&&(koloda[i]->GetKardMast()==piki)) return DropKard(i);

    if((!mastFlagTmp)&&(!mastFlagDamaPikTmp)&&(mastFlagCherviTmp)) // Кидаем подляну - Старшую черву
    {   //
        //tmpResultKardNom=-1;
        tmpResultKardNominal=1;
        for(int i=0;i<koloda.size();i++)
            if(
                 (koloda[i]->GetKardMast()==chervi)&&
                 (koloda[i]->GetKardNom()>=tmpResultKardNominal)
              )
            {
                tmpResultKardNom=i;
                tmpResultKardNominal=koloda[i]->GetKardNom();
            };
        {SetTuzNom();return DropKard(tmpResultKardNom);};
    };
    //
    tmpResultKardNominal=1;
    for(int i=0;i<koloda.size();i++)
            if(koloda[i]->GetKardNom()>=tmpResultKardNominal)
            {
                tmpResultKardNom=i;
                tmpResultKardNominal=koloda[i]->GetKardNom();
            };
    SetTuzNom();
    return DropKard(tmpResultKardNom);
    //DropKard(2);
    //
}
void KartGamer::SetTuzNom()
{
    for(int i=0;i<koloda.size();i++)
        if((koloda[i]->GetKardNom()==13)||(koloda[i]->GetKardNom()==0)) koloda[i]->SetTuzNom();
}
void KartGamer::SetScore(int dn) {score=dn;}
void KartGamer::SetPlusScore(int dn) {score+=dn;}
short int KartGamer::GetScore(){return score;}
short int KartGamer::GetKolodaSize(){return koloda.size();}
