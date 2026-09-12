#include "liga.h"

CLiga::CLiga(std::vector<CDruzyna> druzyny)
: druzyny{druzyny}
{

}

void CLiga::generujTerminarz()
{
    terminarz.clear();
    indeksMeczu = 0;
    for (std::size_t i = 0; i < druzyny.size(); ++i) {
        for (std::size_t j = i +1 ; j < druzyny.size(); ++j) {
            terminarz.push_back({i, j});
        }
    }
}

std::size_t CLiga::getLiczbaMeczow() const
{
    return terminarz.size();
}

bool CLiga::czySaMecze() const
{
    return indeksMeczu < terminarz.size();
}