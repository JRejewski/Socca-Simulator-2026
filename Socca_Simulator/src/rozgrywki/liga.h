#ifndef LIGA_H
#define LIGA_H

#include <vector>
#include "../druzyny/druzyna.h"
#include <utility>
#include <cstddef>
#include <optional>

/**
 * @brief Wiersz tabeli ligowej pojedynczej drużyny.
 *
 * Struktura przechowuje statystyki jednej drużyny zgromadzone
 * w trakcie rozgrywek ligowych (CLiga).
 */
struct WierszTabeli
{
    int rozegrane{0}; ///< Liczba rozegranych meczów.
    int punkty{0}; ///< Liczba zdobytych punktów (3 za zwycięstwo, 1 za remis).
    int bramkiStracone{0}; ///< Liczba bramek straconych.
    int bramkiZdobyte{0}; ///< Liczba bramek zdobytych.
    int roznicaBramek{0}; ///< Różnica bramek (bramkiZdobyte - bramkiStracone).
};

/**
 * @brief Wynik pojedynczego rozegranego meczu ligowego.
 *
 * Indeksy gospodarze i goscie odnoszą się do pozycji odpowiednich
 * drużyn w wektorze drużyn przekazanym do konstruktora CLiga.
 */
struct WynikMeczu
{
    std::size_t gospodarze{0}; ///< Indeks drużyny gospodarzy w tabeli drużyn.
    std::size_t goscie{0}; ///< Indeks drużyny gości w tabeli drużyn.
    int goleGospodarzy{0}; ///< Liczba bramek zdobytych przez gospodarzy.
    int goleGosci{0}; ///< Liczba bramek zdobytych przez gości.
};

/**
 * @brief Klasa zarządzająca rozgrywkami ligowymi.
 *
 * CLiga generuje terminarz meczów systemem "każdy z każdym"
 * (bez rewanżów), pozwala rozegrywać kolejne mecze terminarza
 * pojedynczo oraz udostępnia bieżącą tabelę ligową posortowaną
 * według liczby punktów, a w przypadku remisu punktowego -
 * według różnicy bramek.
 */
class CLiga
{
public:
    /**
     * @brief Tworzy ligę dla podanego zbioru drużyn.
     * @param druzyny Drużyny biorące udział w rozgrywkach.
     */
    CLiga(std::vector<CDruzyna> druzyny);

    /**
     * @brief Generuje terminarz rozgrywek systemem "każdy z każdym".
     *
     * Czyści dotychczasowy terminarz, zeruje indeks bieżącego meczu,
     * resetuje ostatni wynik oraz tabelę ligową wszystkich drużyn.
     */
    void generujTerminarz();

    /**
     * @brief Zwraca łączną liczbę meczów w terminarzu.
     * @return Liczba wszystkich meczów do rozegrania w danej edycji ligi.
     */
    std::size_t getLiczbaMeczow() const;

    /**
     * @brief Sprawdza, czy w terminarzu pozostały jeszcze mecze do rozegrania.
     * @return true, jeśli są jeszcze nierozegrane mecze; w przeciwnym razie false.
     */
    bool czySaMecze()const;

    /**
     * @brief Rozgrywa kolejny mecz z terminarza.
     *
     * Jeżeli nie ma już meczów do rozegrania (czySaMecze() zwraca false),
     * metoda nie robi nic. W przeciwnym razie symuluje kolejny mecz,
     * aktualizuje tabelę ligową obu drużyn (rozegrane, punkty, bramki),
     * zapisuje wynik meczu jako ostatni wynik oraz przesuwa indeks
     * bieżącego meczu na kolejną pozycję terminarza.
     *
     * @param ziarno Ziarno generatora liczb pseudolosowych przekazywane
     *        do symulacji meczu.
     */
    void rozegrajNastepnyMecz(unsigned int ziarno);

    /**
     * @brief Zwraca statystyki ligowe drużyny o podanym indeksie.
     * @param indeks Indeks drużyny w wektorze drużyn przekazanym do konstruktora.
     * @return Wiersz tabeli ligowej dla wskazanej drużyny.
     */
    WierszTabeli getStatystyki(std::size_t indeks) const;

    /**
     * @brief Zwraca kolejność drużyn w tabeli ligowej.
     *
     * Drużyny są sortowane malejąco według liczby punktów,
     * a w przypadku równej liczby punktów - malejąco według
     * różnicy bramek (zob. czyWyzej()).
     *
     * @return Wektor indeksów drużyn w kolejności od pierwszego
     *         do ostatniego miejsca w tabeli.
     */
    std::vector<std::size_t> getKolejnoscTabeli() const;

    /**
     * @brief Zwraca wynik ostatnio rozegranego meczu ligowego.
     * @return Wynik ostatniego meczu, jeśli jakikolwiek mecz został już
     *         rozegrany od czasu ostatniego wywołania generujTerminarz();
     *         w przeciwnym razie std::nullopt.
     */
    std::optional<WynikMeczu> getOstatniWynik() const;


private:
    std::vector<CDruzyna> druzyny; ///< Drużyny biorące udział w rozgrywkach.
    std::vector<std::pair<std::size_t, std::size_t>> terminarz; ///< Terminarz meczów (pary indeksów drużyn: gospodarz, gość).
    std::size_t indeksMeczu{0}; ///< Indeks kolejnego meczu w terminarzu do rozegrania.
    std::vector<WierszTabeli> tabela; ///< Bieżąca tabela ligowa (statystyki poszczególnych drużyn).

    /**
     * @brief Porównuje pozycję dwóch drużyn w tabeli ligowej.
     *
     * Drużyna a jest wyżej w tabeli niż drużyna b, jeśli ma więcej
     * punktów, a przy równej liczbie punktów - lepszą różnicę bramek.
     *
     * @param a Indeks pierwszej drużyny.
     * @param b Indeks drugiej drużyny.
     * @return true, jeśli drużyna a znajduje się wyżej w tabeli niż drużyna b.
     */
    bool czyWyzej(std::size_t a, std::size_t b) const;
    std::optional<WynikMeczu> ostatniWynik; ///< Wynik ostatnio rozegranego meczu (jeśli istnieje).
};

#endif // LIGA_H
