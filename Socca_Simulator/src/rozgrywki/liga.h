#ifndef LIGA_H
#define LIGA_H

#include <vector>
#include "../druzyny/druzyna.h"
#include <utility>
#include <cstddef>
#include <optional>

struct WierszTabeli
{
    int rozegrane{0};
    int punkty{0};
    int bramkiStracone{0};
    int bramkiZdobyte{0};
    int roznicaBramek{0};
};

struct WynikMeczu
{
    std::size_t gospodarze{0};
    std::size_t goscie{0};
    int goleGospodarzy{0};
    int goleGosci{0};
};

class CLiga
{
public:
    CLiga(std::vector<CDruzyna> druzyny);

    void generujTerminarz();
    std::size_t getLiczbaMeczow() const;
    bool czySaMecze()const;
    void rozegrajNastepnyMecz(unsigned int ziarno);
    WierszTabeli getStatystyki(std::size_t indeks) const;
    std::vector<std::size_t> getKolejnoscTabeli() const;
    std::optional<WynikMeczu> getOstatniWynik() const;


private:
    std::vector<CDruzyna> druzyny;
    std::vector<std::pair<std::size_t, std::size_t>> terminarz;
    std::size_t indeksMeczu{0};
    std::vector<WierszTabeli> tabela;
    bool czyWyzej(std::size_t a, std::size_t b) const;
    std::optional<WynikMeczu> ostatniWynik;
};

#endif // LIGA_H
