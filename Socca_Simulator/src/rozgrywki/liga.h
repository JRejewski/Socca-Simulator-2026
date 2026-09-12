#ifndef LIGA_H
#define LIGA_H

#include <vector>
#include "../druzyny/druzyna.h"
#include <utility>
#include <cstddef>

class CLiga
{
public:
    CLiga(std::vector<CDruzyna> druzyny);

    void generujTerminarz();
    std::size_t getLiczbaMeczow() const;
    bool czySaMecze()const;


private:
    std::vector<CDruzyna> druzyny;
    std::vector<std::pair<std::size_t, std::size_t>> terminarz;
    std::size_t indeksMeczu{0};
};

#endif // LIGA_H
