#ifndef BRAMKARZ_H
#define BRAMKARZ_H

#include "zawodnik.h"

/**
 * @brief Klasa reprezentująca bramkarza drużyny.
 *
 * CBramkarz dziedziczy po CZawodnik i rozszerza go o atrybuty
 * charakterystyczne dla bramkarza: pozycjonowanie, inteligencję
 * i parady. Udostępnia metodę obliczającą siłę bramkarza,
 * wykorzystywaną przy symulacji meczu do wyliczenia szansy na
 * strzelenie gola przeciwnej drużynie.
 */
class CBramkarz : public CZawodnik
{
public:
    /**
     * @brief Tworzy nowego bramkarza.
     * @param imie Imię bramkarza.
     * @param nazwisko Nazwisko bramkarza.
     * @param celnosc Atrybut celności (zostanie ograniczony do zakresu [1, 100]).
     * @param fizycznosc Atrybut fizyczności (zostanie ograniczony do zakresu [1, 100]).
     * @param charyzma Atrybut charyzmy (zostanie ograniczony do zakresu [1, 100]).
     * @param pozycjonowanie Atrybut pozycjonowania (zostanie ograniczony do zakresu [1, 100]).
     * @param inteligencja Atrybut inteligencji (zostanie ograniczony do zakresu [1, 100]).
     * @param parady Atrybut skuteczności parad (zostanie ograniczony do zakresu [1, 100]).
     */
    CBramkarz(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma, int pozycjonowanie, int inteligencja, int parady);

    /**
     * @brief Zwraca wartość atrybutu pozycjonowania.
     * @return Pozycjonowanie bramkarza w zakresie [1, 100].
     */
    int getPozycjonowanie() const;

    /**
     * @brief Zwraca wartość atrybutu inteligencji.
     * @return Inteligencja bramkarza w zakresie [1, 100].
     */
    int getInteligencja() const;

    /**
     * @brief Zwraca wartość atrybutu parad.
     * @return Skuteczność parad bramkarza w zakresie [1, 100].
     */
    int getParady() const;

    /**
     * @brief Oblicza siłę bramkarza.
     *
     * Siła bramkarza jest średnią arytmetyczną atrybutów:
     * pozycjonowania, inteligencji, parad oraz fizyczności
     * (odziedziczonej z CZawodnik).
     *
     * @return Siła bramkarza.
     */
    double obliczSileBramkarza() const;

private:
    int pozycjonowanie, inteligencja, parady; ///< Atrybuty specyficzne dla bramkarza (zakres [1, 100]).
};

#endif // BRAMKARZ_H
