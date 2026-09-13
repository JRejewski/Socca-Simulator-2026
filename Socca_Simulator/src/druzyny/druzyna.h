#ifndef DRUZYNA_H
#define DRUZYNA_H

#include<string>
#include<array>
#include"../zawodnicy/pilkarz.h"
#include"../zawodnicy/bramkarz.h"

/**
 * @brief Klasa reprezentująca drużynę piłkarską.
 *
 * Drużyna składa się z reprezentowanej nazwy, dokładnie pięciu
 * piłkarzy oraz jednego bramkarza. Klasa udostępnia metody
 * wyliczające zbiorczą siłę ataku, siłę obrony oraz siłę bramkarza
 * całej drużyny, wykorzystywane następnie przy symulacji meczu (Cmecz).
 */
class CDruzyna
{
public:
    /**
     * @brief Tworzy nową drużynę.
     * @param reprezentacja Nazwa reprezentowanej drużyny.
     * @param pilkarze Tablica dokładnie pięciu piłkarzy tworzących drużynę.
     * @param bramkarz Bramkarz drużyny.
     */
    CDruzyna(std::string reprezentacja, std::array<CPilkarz, 5> pilkarze, CBramkarz bramkarz);

    /**
     * @brief Oblicza łączną siłę ataku drużyny.
     *
     * Wartość jest średnią arytmetyczną siły ataku wszystkich
     * piłkarzy drużyny.
     *
     * @return Siła ataku drużyny.
     */
    double obliczSileAtaku() const;

    /**
     * @brief Oblicza łączną siłę obrony drużyny.
     *
     * Wartość jest średnią arytmetyczną siły obrony wszystkich
     * piłkarzy drużyny.
     *
     * @return Siła obrony drużyny.
     */
    double obliczSileObrony() const;

    /**
     * @brief Oblicza siłę bramkarza drużyny.
     * @return Siła bramkarza drużyny.
     */
    double obliczSileBramkarza() const;

    /**
     * @brief Zwraca nazwę drużyny.
     * @return Nazwa reprezentowanej drużyny.
     */
    std::string getNazwa() const;

private:

    std::string reprezentacja; ///< Nazwa reprezentowanej drużyny.
    std::array<CPilkarz, 5> pilkarze; ///< Pięciu piłkarzy tworzących drużynę.
    CBramkarz bramkarz; ///< Bramkarz drużyny.

};

#endif // DRUZYNA_H
