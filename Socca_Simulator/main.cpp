/**
 * @file main.cpp
 * @brief Punkt wejścia aplikacji Socca Simulator.
 */

#include "gui/mainwindow.h"
#include <QApplication>


/**
 * @brief Funkcja główna programu.
 *
 * Tworzy aplikację Qt, wyświetla główne okno programu (MainWindow)
 * i uruchamia pętlę zdarzeń aplikacji.
 *
 * @param argc Liczba argumentów wiersza poleceń.
 * @param argv Tablica argumentów wiersza poleceń.
 * @return Kod wyjścia aplikacji zwrócony przez pętlę zdarzeń Qt.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
