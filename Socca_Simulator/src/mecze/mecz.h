#ifndef MECZ_H
#define MECZ_H

#include"../druzyny/druzyna.h"

class Cmecz
{
public:
    Cmecz(CDruzyna gospodarze, CDruzyna goscie);

    int getGoleGospodarzy() const;
    int getGoleGosci() const;
    void symuluj();


private:
    CDruzyna gospodarze;
    CDruzyna goscie;

    int goleGospodarzy{0};
    int goleGosci{0};
};

#endif // MECZ_H
