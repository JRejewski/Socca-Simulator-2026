#include "mecz.h"

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

void Cmecz::symuluj()
{
    double atak = gospodarze.obliczSileAtaku();
    double obrona = goscie.obliczSileObrony();
    double szansa = atak / (atak + obrona);
}