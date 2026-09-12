#ifndef LIGA_H
#define LIGA_H

#include <vector>
#include "../druzyny/druzyna.h"
#include <utility>
#include <cstddef>

struct WierszTabeli
{
    int rozegrane{0};
    int punkty{0};
    int bramkiStracone{0};
    int bramkiZdobyte{0};
    int roznicaBramek{0};
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


private:
    std::vector<CDruzyna> druzyny;
    std::vector<std::pair<std::size_t, std::size_t>> terminarz;
    std::size_t indeksMeczu{0};
    std::vector<WierszTabeli> tabela;
    bool czyWyzej(std::size_t a, std::size_t b) const;
};

#endif // LIGA_H
