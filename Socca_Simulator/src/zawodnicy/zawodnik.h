#ifndef ZAWODNIK_H
#define ZAWODNIK_H


#include <string>


class CZawodnik
{
public:
    CZawodnik(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma);

    std::string nazwa() const;

    int getFizycznosc() const;
    int getCelnosc() const;
    int getCharyzma() const;


private:
    std::string imie, nazwisko;
    int celnosc, fizycznosc, charyzma;
};
#endif // ZAWODNIK_H
