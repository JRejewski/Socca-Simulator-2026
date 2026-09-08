#ifndef BRAMKARZ_H
#define BRAMKARZ_H

#include "zawodnik.h"

class CBramkarz : public CZawodnik
{
public:
    CBramkarz(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma, int pozycjonowanie, int inteligencja, int parady);

    int getPozycjonowanie() const;
    int getInteligencja() const;
    int getParady() const;

private:
    int pozycjonowanie, inteligencja, parady;
};

#endif // BRAMKARZ_H
