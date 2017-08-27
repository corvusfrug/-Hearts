#ifndef KARTGAMER_H
#define KARTGAMER_H

#include <string>
#include <vector>
#include "Kard.h"

using std::string;
using std::vector;

class KartGamer
{
public:
    KartGamer(string,short int _number);
    virtual ~KartGamer();
    void Print(SDL_Texture* img, SDL_Renderer* rnd);
    void addKard(Kard*);
    Kard* DropKard(int nK=0);
    virtual Kard* Play(int &iterat, Mast vzM, short int vzNM, int MouseX=0,int MouseY=0);
    short int GetScore();
    short int GetKolodaSize();
    void SetScore(int);
    void SetPlusScore(int);

protected:
    short int score;
    short int number;
    string name;
    vector <Kard*> koloda;
    int posX;
    int posY;
private:
    void SetTuzNom();

};

#endif // KARTGAMER_H
