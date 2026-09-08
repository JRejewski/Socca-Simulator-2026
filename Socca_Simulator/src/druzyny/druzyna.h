#ifndef DRUZYNA_H
#define DRUZYNA_H

#include<string>
#include<array>
#include"../zawodnicy/pilkarz.h"
#include"../zawodnicy/bramkarz.h"

class CDruzyna
{
public:
    CDruzyna(std::string reprezentacja, std::array<CPilkarz, 5> pilkarze, CBramkarz bramkarz);

    double obliczSileAtaku() const;
    double obliczSileObrony() const;
    double obliczSileBramkarza() const;

private:

    std::string reprezentacja;
    std::array<CPilkarz, 5> pilkarze;
    CBramkarz bramkarz;

};

#endif // DRUZYNA_H
