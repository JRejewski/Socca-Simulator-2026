#include "bramkarz.h"

CBramkarz::CBramkarz(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma, int pozycjonowanie, int inteligencja, int parady):
    CZawodnik{imie, nazwisko, celnosc, fizycznosc, charyzma},
    pozycjonowanie{pozycjonowanie},
    inteligencja{inteligencja},
    parady{parady}

{
    if (pozycjonowanie > 100)
    {
        this->pozycjonowanie = 100;
    }
    else if (pozycjonowanie < 1)
    {
        this->pozycjonowanie = 1;
    }


    if (inteligencja > 100)
    {
        this->inteligencja = 100;
    }
    else if (inteligencja < 1)
    {
        this->inteligencja = 1;
    }


    if (parady > 100)
    {
        this->parady = 100;
    }
    else if (parady < 1)
    {
        this->parady = 1;
    }
}

int CBramkarz::getPozycjonowanie() const
{
    return pozycjonowanie;
}

int CBramkarz::getInteligencja() const
{
    return inteligencja;
}

int CBramkarz::getParady() const
{
    return parady;
}

double CBramkarz::obliczSileBramkarza() const
{
    double silaObrony = (pozycjonowanie + inteligencja + parady + getFizycznosc()) / 4.0;
    return silaObrony;
}