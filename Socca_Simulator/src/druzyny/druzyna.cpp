#include "druzyna.h"

CDruzyna::CDruzyna(std::string reprezentacja, std::array<CPilkarz, 5> pilkarze, CBramkarz bramkarz):
    reprezentacja{reprezentacja},
    pilkarze{pilkarze},
    bramkarz{bramkarz}

{

}

double CDruzyna::obliczSileAtaku() const
{
    double atak = 0.0;
    for (std::size_t i = 0; i < pilkarze.size(); ++i) {
        atak = atak + pilkarze[i].obliczSileAtaku();
    }
    atak = atak / 5.0;
    return atak;
}

double CDruzyna::obliczSileObrony() const
{
    double obrona = 0.0;
    for (std::size_t i = 0; i < pilkarze.size(); ++i) {
        obrona = obrona + pilkarze[i].obliczSileObrony();
    }
    obrona = obrona / 5.0;
    return obrona;
}

double CDruzyna::obliczSileBramkarza() const
{
    return bramkarz.obliczSileBramkarza();
}

std::string CDruzyna::getNazwa() const
{
    return reprezentacja;
}