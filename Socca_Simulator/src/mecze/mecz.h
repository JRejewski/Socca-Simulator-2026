#ifndef MECZ_H
#define MECZ_H

#include"../druzyny/druzyna.h"

/**
 * @brief Klasa reprezentująca pojedynczy mecz pomiędzy dwiema drużynami.
 *
 * Cmecz przechowuje drużynę gospodarzy i gości oraz wynik ostatniej
 * symulacji. Symulacja przebiega w oparciu o wyliczone wcześniej
 * siły ataku, obrony i bramkarza obu drużyn (zob. CDruzyna) oraz
 * generator liczb pseudolosowych zainicjalizowany podanym ziarnem,
 * dzięki czemu wynik meczu jest odtwarzalny dla tego samego ziarna.
 */
class Cmecz
{
public:
    /**
     * @brief Tworzy mecz pomiędzy dwiema drużynami.
     * @param gospodarze Drużyna gospodarzy.
     * @param goscie Drużyna gości.
     */
    Cmecz(CDruzyna gospodarze, CDruzyna goscie);

    /**
     * @brief Zwraca liczbę goli strzelonych przez gospodarzy.
     * @return Liczba bramek gospodarzy po ostatniej symulacji.
     */
    int getGoleGospodarzy() const;

    /**
     * @brief Zwraca liczbę goli strzelonych przez gości.
     * @return Liczba bramek gości po ostatniej symulacji.
     */
    int getGoleGosci() const;

    /**
     * @brief Symuluje przebieg meczu.
     *
     * Mecz składa się z dziesięciu akcji. W każdej akcji obie drużyny
     * mają, zgodnie z proporcją swojej siły ataku do siły obrony
     * przeciwnika, szansę na oddanie strzelistej akcji, a następnie,
     * zgodnie z proporcją siły ataku do siły bramkarza przeciwnika,
     * szansę na zdobycie gola. Wywołanie resetuje dotychczasowy wynik
     * meczu (goleGospodarzy i goleGosci) do zera.
     *
     * @param ziarno Ziarno generatora liczb pseudolosowych, decydujące
     *        o przebiegu i wyniku symulacji.
     */
    void symuluj(unsigned int ziarno);


private:
    CDruzyna gospodarze; ///< Drużyna gospodarzy.
    CDruzyna goscie; ///< Drużyna gości.

    int goleGospodarzy{0}; ///< Liczba bramek strzelonych przez gospodarzy.
    int goleGosci{0}; ///< Liczba bramek strzelonych przez gości.
};

#endif // MECZ_H
