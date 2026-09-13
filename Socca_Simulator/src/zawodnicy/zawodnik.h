#ifndef ZAWODNIK_H
#define ZAWODNIK_H


#include <string>


/**
 * @brief Bazowa klasa reprezentująca zawodnika drużyny.
 *
 * Klasa CZawodnik przechowuje dane wspólne dla wszystkich zawodników:
 * dane osobowe (imię i nazwisko) oraz podstawowe atrybuty liczbowe
 * (celność, fizyczność, charyzma) wykorzystywane później przy obliczaniu
 * siły drużyny. Jest klasą bazową dla klas CPilkarz oraz CBramkarz.
 *
 * Wszystkie atrybuty liczbowe są ograniczane do zakresu [1, 100]
 * już w konstruktorze.
 */
class CZawodnik
{
public:
    /**
     * @brief Tworzy nowego zawodnika.
     * @param imie Imię zawodnika.
     * @param nazwisko Nazwisko zawodnika.
     * @param celnosc Atrybut celności (zostanie ograniczony do zakresu [1, 100]).
     * @param fizycznosc Atrybut fizyczności (zostanie ograniczony do zakresu [1, 100]).
     * @param charyzma Atrybut charyzmy (zostanie ograniczony do zakresu [1, 100]).
     */
    CZawodnik(std::string imie, std::string nazwisko, int celnosc, int fizycznosc, int charyzma);

    /**
     * @brief Zwraca pełną nazwę zawodnika.
     * @return Imię i nazwisko połączone spacją.
     */
    std::string nazwa() const;

    /**
     * @brief Zwraca wartość atrybutu fizyczności.
     * @return Fizyczność zawodnika w zakresie [1, 100].
     */
    int getFizycznosc() const;

    /**
     * @brief Zwraca wartość atrybutu celności.
     * @return Celność zawodnika w zakresie [1, 100].
     */
    int getCelnosc() const;

    /**
     * @brief Zwraca wartość atrybutu charyzmy.
     * @return Charyzma zawodnika w zakresie [1, 100].
     */
    int getCharyzma() const;


private:
    std::string imie, nazwisko; ///< Imię i nazwisko zawodnika.
    int celnosc, fizycznosc, charyzma; ///< Podstawowe atrybuty liczbowe zawodnika (zakres [1, 100]).
};
#endif // ZAWODNIK_H
