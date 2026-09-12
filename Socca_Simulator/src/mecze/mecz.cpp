#include "mecz.h"
#include <random>

Cmecz::Cmecz(CDruzyna gospodarze, CDruzyna goscie):
    gospodarze{gospodarze},
    goscie{goscie}

{

}

int Cmecz::getGoleGospodarzy() const
{
    return goleGospodarzy;
}

int Cmecz::getGoleGosci() const
{
    return goleGosci;
}

void Cmecz::symuluj(unsigned int ziarno)
{
    goleGosci = 0;
    goleGospodarzy = 0;
    std::mt19937 generator{ziarno};
    std::uniform_real_distribution<double> losowanie{0.0, 1.0};
    for (int i = 0; i < 10; ++i)
    {
        double losGosp = losowanie(generator);
        double atakGosp = gospodarze.obliczSileAtaku();
        double obronaGosc = goscie.obliczSileObrony();
        double szansaGosp = atakGosp / (atakGosp + obronaGosc);
        if (losGosp < szansaGosp)
        {
            double szansaGolaGosp = atakGosp / (atakGosp + goscie.obliczSileBramkarza());
            double losGolGosp = losowanie(generator);
            if (losGolGosp < szansaGolaGosp)
            {
                ++goleGospodarzy;
            }
        }

        double losGosc = losowanie(generator);
        double atakGosc = goscie.obliczSileAtaku();
        double obronaGosp = gospodarze.obliczSileObrony();
        double szansaGosc = atakGosc / (atakGosc + obronaGosp);
        if (losGosc < szansaGosc)
        {
            double szansaGolaGosc = atakGosc / (atakGosc + gospodarze.obliczSileBramkarza());
            double losGolGosc = losowanie(generator);
            if (losGolGosc < szansaGolaGosc)
            {
                ++goleGosci;
            }
        }
    }
}