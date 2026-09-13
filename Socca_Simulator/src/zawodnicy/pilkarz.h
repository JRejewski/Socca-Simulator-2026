#ifndef PILKARZ_H
#define PILKARZ_H

#include "zawodnik.h"

/**
 * @brief Klasa reprezentująca zawodnika polowego (piłkarza).
 *
 * CPilkarz dziedziczy po CZawodnik i rozszerza go o atrybuty
 * charakterystyczne dla zawodnika polowego: szybkość, technikę
 * i defensywę. Udostępnia metody obliczające siłę ataku oraz
 * siłę obrony pojedynczego piłkarza, wykorzystywane następnie
 * przez CDruzyna do wyliczenia siły całej drużyny.
 */
class CPilkarz : public CZawodnik
{
public:
    /**
     * @brief Tworzy nowego piłkarza.
     * @param imie Imię piłkarza.
     * @param nazwisko Nazwisko piłkarza.
     * @param celnosc Atrybut celności (zostanie ograniczony do zakresu [1, 100]).
     * @param fizycznosc Atrybut fizyczności (zostanie ograniczony do zakresu [1, 100]).
     * @param charyzma Atrybut charyzmy (zostanie ograniczony do zakresu [1, 100]).
     * @param szybkosc Atrybut szybkości (zostanie ograniczony do zakresu [1, 100]).
     * @param technika Atrybut techniki (zostanie ograniczony do zakresu [1, 100]).
     * @param defensywa Atrybut defensywy (zostanie ograniczony do zakresu [1, 100]).
     */
    CPilkarz(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma, int szybkosc, int technika, int defensywa);


    /**
     * @brief Zwraca wartość atrybutu szybkości.
     * @return Szybkość piłkarza w zakresie [1, 100].
     */
    int getSzybkosc() const;

    /**
     * @brief Zwraca wartość atrybutu techniki.
     * @return Technika piłkarza w zakresie [1, 100].
     */
    int getTechnika() const;

    /**
     * @brief Zwraca wartość atrybutu defensywy.
     * @return Defensywa piłkarza w zakresie [1, 100].
     */
    int getDefensywa() const;

    /**
     * @brief Oblicza siłę ataku piłkarza.
     *
     * Siła ataku jest średnią arytmetyczną atrybutów: celności,
     * szybkości i techniki.
     *
     * @return Siła ataku piłkarza.
     */
    double obliczSileAtaku() const;

    /**
     * @brief Oblicza siłę obrony piłkarza.
     *
     * Siła obrony jest średnią arytmetyczną atrybutów: fizyczności,
     * charyzmy i defensywy.
     *
     * @return Siła obrony piłkarza.
     */
    double obliczSileObrony() const;

private:
    int szybkosc, technika, defensywa; ///< Atrybuty specyficzne dla piłkarza (zakres [1, 100]).
};

#endif // PILKARZ_H
