#include "gui/mainwindow.h"
#include "src/zawodnicy/zawodnik.h"
#include <QDebug>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CZawodnik gracz{"Jan", "Kowalski", 100, 0, 60};
    int wynik = gracz.getCelnosc();
    qDebug() << wynik;

    MainWindow w;
    w.show();
    return QApplication::exec();
}
