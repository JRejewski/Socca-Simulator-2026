#ifndef WCZYTYWACZDRUZYN_H
#define WCZYTYWACZDRUZYN_H

#include <vector>
#include <QString>
#include "../druzyny/druzyna.h"

/**
 * @brief Wczytuje i sprawdza dane drużyn zapisane w formacie JSON.
 *
 * Klasa odpowiada za odczyt pliku (lub zasobu Qt) z danymi drużyn
 * oraz zbudowanie na ich podstawie kolekcji gotowych obiektów
 * CDruzyna, wraz z ich piłkarzami i bramkarzem.
 */
class CWczytywaczDruzyn
{
public:
    /** @brief Tworzy wczytywacz danych drużyn. */
    CWczytywaczDruzyn();

    /**
     * @brief Wczytuje drużyny wraz z piłkarzami i bramkarzami.
     * @param sciezka Ścieżka pliku lub zasobu Qt (np. ":/data/druzyny.json").
     * @return Kolekcja poprawnie wczytanych drużyn.
     * @throws std::runtime_error Gdy odczyt, format JSON lub dane są niepoprawne.
     */
    std::vector<CDruzyna> wczytaj(const QString& sciezka) const;
};

#endif // WCZYTYWACZDRUZYN_H
