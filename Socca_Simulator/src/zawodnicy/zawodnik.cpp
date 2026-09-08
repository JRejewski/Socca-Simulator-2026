#include "zawodnik.h"

CZawodnik::CZawodnik(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma)
    : imie{imie},
    nazwisko{nazwisko},
    celnosc{celnosc},
    fizycznosc{fizycznosc},
    charyzma{charyzma}
{
    if (celnosc > 100)
    {
        this->celnosc = 100;
    }
    else if (celnosc < 1)
    {
        this->celnosc = 1;
    }


    if (fizycznosc > 100)
    {
        this->fizycznosc = 100;
    }
    else if (fizycznosc < 1)
    {
        this->fizycznosc = 1;
    }


    if (charyzma > 100)
    {
        this->charyzma = 100;
    }
    else if (charyzma < 1)
    {
        this->charyzma = 1;
    }
}

std::string CZawodnik::nazwa() const
{
    return imie + " " + nazwisko;
}

int CZawodnik::getFizycznosc() const
{
    return fizycznosc;
}

int CZawodnik::getCelnosc() const
{
    return celnosc;
}

int CZawodnik::getCharyzma() const
{
    return charyzma;
}