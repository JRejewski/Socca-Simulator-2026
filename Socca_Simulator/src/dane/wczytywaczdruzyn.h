#ifndef WCZYTYWACZDRUZYN_H
#define WCZYTYWACZDRUZYN_H

#include <vector>
#include <QString>
#include "../druzyny/druzyna.h"

/**
 * @brief Wczytuje i sprawdza dane druzyn zapisane w JSON.
 */
class CWczytywaczDruzyn
{
public:
    /** @brief Tworzy wczytywacz danych druzyn. */
    CWczytywaczDruzyn();

    /**
     * @brief Wczytuje druzyny wraz z pilkarzami i bramkarzami.
     * @param sciezka Sciezka pliku lub zasobu Qt.
     * @return Kolekcja poprawnie wczytanych druzyn.
     * @throws std::runtime_error Gdy odczyt, format JSON lub dane sa niepoprawne.
     */
    std::vector<CDruzyna> wczytaj(const QString& sciezka) const;
};

#endif // WCZYTYWACZDRUZYN_H
