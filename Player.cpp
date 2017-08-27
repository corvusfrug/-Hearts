#include "Player.h"

Kard* Player::Play(int &iterat, Mast vzM, short int vzNM, int MouseX,int MouseY)
{
    bool mastFlagTmp=false;
    for(int i=0;i<koloda.size();i++)
        if((koloda[i]->GetKardMast()==vzM)||
           (vzM==NaM))
            mastFlagTmp=true;
    //std::cout << "ErrPlay1!!\n";
    for(int i= koloda.size()-1;i>=0;i--)
    {
        if(
           (koloda[i]->GetKardX() <  MouseX)                       &&
           (koloda[i]->GetKardX()+koloda[i]->GetKardW() >  MouseX) &&
           (koloda[i]->GetKardY() <  MouseY)                       &&
           (koloda[i]->GetKardY()+koloda[i]->GetKardH() >  MouseY)
          )
        {
            //std::cout << "ErrPlay2!!\n";
            if(iterat<4)
                if(
                       (koloda[i]->GetKardMast()==chervi) ||
                       (
                          (koloda[i]->GetKardMast()==piki) &&
                          (koloda[i]->GetKardNom()==11)
                       )
                  ) return NULL;
            if(iterat==0)
                if(
                     (koloda[i]->GetKardMast()==tref)&&
                     (koloda[i]->GetKardNom()==1)
                  )
                return DropKard(i); else return NULL;
            else
                if
                (
                  (koloda[i]->GetKardMast() == vzM) ||
                  (vzM==NaM) || ((!mastFlagTmp))
                )
                return DropKard(i); else return NULL;
        };
        //std::cout << "ErrPlay3!!\n";

    };
    //std::cout << "ErrPlay4!!\n";
    return NULL;
}

Player::Player(string _name,short int _number=0)
: KartGamer(_name,_number)
{
    /*name=_name;
    number=_number;*/
    posX=400;
    posY=450;
};

