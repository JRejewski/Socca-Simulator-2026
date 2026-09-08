#ifndef PILKARZ_H
#define PILKARZ_H

#include "zawodnik.h"

class CPilkarz : public CZawodnik
{
public:
    CPilkarz(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma, int szybkosc, int technika, int defensywa);


    int getSzybkosc() const;
    int getTechnika() const;
    int getDefensywa() const;

    double obliczSileAtaku() const;
    double obliczSileObrony() const;

private:
    int szybkosc, technika, defensywa;
};

#endif // PILKARZ_H
