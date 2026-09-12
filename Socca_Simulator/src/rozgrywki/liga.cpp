#include "liga.h"
#include "../mecze/mecz.h"
#include <algorithm>

CLiga::CLiga(std::vector<CDruzyna> druzyny)
: druzyny{druzyny}
{

}

void CLiga::generujTerminarz()
{
    terminarz.clear();
    indeksMeczu = 0;
    tabela.assign(druzyny.size(), WierszTabeli{});
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

void CLiga::rozegrajNastepnyMecz(unsigned int ziarno)
{
    if (!czySaMecze())
    {
        return;
    }
    auto para = terminarz[indeksMeczu];
    Cmecz mecz(druzyny[para.first], druzyny[para.second]);
    mecz.symuluj(ziarno);
    int goleGospodarzy = mecz.getGoleGospodarzy();
    int goleGosci = mecz.getGoleGosci();
    ++tabela[para.first].rozegrane;
    ++tabela[para.second].rozegrane;
    tabela[para.first].bramkiZdobyte += goleGospodarzy;
    tabela[para.first].bramkiStracone += goleGosci;
    tabela[para.second].bramkiZdobyte += goleGosci;
    tabela[para.second].bramkiStracone += goleGospodarzy;
    tabela[para.first].roznicaBramek += (goleGospodarzy - goleGosci);
    tabela[para.second].roznicaBramek += (goleGosci - goleGospodarzy);
    if (goleGospodarzy > goleGosci)
    {
        tabela[para.first].punkty += 3;
    }
    else if (goleGosci > goleGospodarzy)
    {
        tabela[para.second].punkty += 3;
    }
    else
    {
        ++tabela[para.first].punkty;
        ++tabela[para.second].punkty;
    }
    ++indeksMeczu;
}

WierszTabeli CLiga::getStatystyki(std::size_t indeks) const
{
    return tabela.at(indeks);
}

std::vector<std::size_t> CLiga::getKolejnoscTabeli() const
{
    std::vector<std::size_t> kolejnosc;

    for (std::size_t i = 0; i < druzyny.size(); ++i)
    {
        kolejnosc.push_back(i);
    }
    std::sort(kolejnosc.begin(), kolejnosc.end(),
              [this](std::size_t a, std::size_t b)
              {
                  return czyWyzej(a, b);
              });
    return kolejnosc;
}

bool CLiga::czyWyzej(std::size_t a, std::size_t b) const
{
    if (tabela[a].punkty != tabela[b].punkty)
    {
        return tabela[a].punkty > tabela[b].punkty;
    }

    return tabela[a].roznicaBramek > tabela[b].roznicaBramek;
}