#include "gui/mainwindow.h"
#include "src/zawodnicy/zawodnik.h"
#include "src/zawodnicy/pilkarz.h"
#include "src/zawodnicy/bramkarz.h"
#include <QDebug>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CBramkarz gracz{"Jan", "Kowalski", 20, 30, 40, 50, 60, 70};
    int q = gracz.getCelnosc();
    qDebug() << q;
    int u = gracz.getFizycznosc();
    qDebug() << u;
    int e = gracz.getCharyzma();
    qDebug() << e;
    int r = gracz.getPozycjonowanie();
    qDebug() << r;
    int t = gracz.getInteligencja();
    qDebug() << t;
    int y = gracz.getParady();
    qDebug() << y;

    MainWindow w;
    w.show();
    return QApplication::exec();
}
