#include "pilkarz.h"

CPilkarz::CPilkarz(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma, int szybkosc, int technika, int defensywa):
    CZawodnik{imie, nazwisko, celnosc, fizycznosc, charyzma},
    szybkosc{szybkosc},
    technika{technika},
    defensywa{defensywa}
{
    if (szybkosc > 100)
    {
        this->szybkosc = 100;
    }
    else if (szybkosc < 1)
    {
        this->szybkosc = 1;
    }


    if (technika > 100)
    {
        this->technika = 100;
    }
    else if (technika < 1)
    {
        this->technika = 1;
    }


    if (defensywa > 100)
    {
        this->defensywa = 100;
    }
    else if (defensywa < 1)
    {
        this->defensywa = 1;
    }
}

int CPilkarz::getSzybkosc() const
{
    return szybkosc;
}

int CPilkarz::getTechnika() const
{
    return technika;
}

int CPilkarz::getDefensywa() const
{
    return defensywa;
}