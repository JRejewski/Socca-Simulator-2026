#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "../src/mecze/mecz.h"
#include <QString>
#include <random>
#include <QComboBox>
#include "../src/rozgrywki/liga.h"
#include <QDebug>
#include <QTableWidget>
#include <QStringList>
#include "../src/dane/wczytywaczdruzyn.h"
#include <QMessageBox>
#include <stdexcept>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabelaLigiWidget->setColumnCount(7);
    ui->tabelaLigiWidget->setHorizontalHeaderLabels(
        {"Miejsce", "Drużyna", "Mecze", "Punkty",
         "Zdobyte", "Stracone", "Bilans"});
    ui->tabelaLigiWidget->setEditTriggers(
        QAbstractItemView::NoEditTriggers);

    try
    {
        przygotujDruzyny();
    }
    catch (const std::exception& blad)
    {
        QMessageBox::critical(
            this,
            "Blad wczytywania druzyn",
            QString::fromUtf8(blad.what()));

        ui->centralwidget->setEnabled(false);
        return;
    }

    ui->tabelaLigiWidget->setRowCount(static_cast<int>(druzyny.size()));

    liga.emplace(druzyny);
    liga->generujTerminarz();
    odswiezTabele();

    for (std::size_t i = 0; i < druzyny.size(); ++i)
    {
        ui->gospodarzeComboBox->addItem(
            QString::fromStdString(druzyny[i].getNazwa()));
        ui->goscieComboBox->addItem(
            QString::fromStdString(druzyny[i].getNazwa()));
    }

    ui->gospodarzeComboBox->setCurrentIndex(-1);
    ui->goscieComboBox->setCurrentIndex(-1);

    pokazMenu();
    connect(ui->symulujButton, &QPushButton::clicked,
            this, &MainWindow::symulujMecz);
    connect(ui->szybkiMeczButton, &QPushButton::clicked,
            this, &MainWindow::pokazSzybkiMecz);
    connect(ui->powrotButton, &QPushButton::clicked,
            this, &MainWindow::pokazMenu);
    connect(ui->ligaButton, &QPushButton::clicked,
            this, &MainWindow::pokazLige);
    connect(ui->powrotLigaButton, &QPushButton::clicked,
            this, &MainWindow::pokazMenu);
    connect(ui->nastepnyMeczButton, &QPushButton::clicked,
            this, &MainWindow::rozegrajMeczLigi);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::symulujMecz()
{
    int idGospodarzy = ui->gospodarzeComboBox->currentIndex();
    int idGosci = ui->goscieComboBox->currentIndex();
    if (idGospodarzy < 0 || idGosci < 0)
    {
        ui->wynikLabel->setText("Wybierz obie drużyny.");
        return;
    }
    if (idGospodarzy == idGosci)
    {
        ui->wynikLabel->setText("Wybierz dwie różne drużyny.");
        return;
    }
    Cmecz mecz{druzyny[idGospodarzy], druzyny[idGosci]};
    std::random_device zrodlo;
    unsigned int ziarno = zrodlo();
    mecz.symuluj(ziarno);

    ui->wynikLabel->setText(
        QString("%1  %2 : %3  %4")
            .arg(QString::fromStdString(druzyny[idGospodarzy].getNazwa()))
            .arg(mecz.getGoleGospodarzy())
            .arg(mecz.getGoleGosci())
            .arg(QString::fromStdString(druzyny[idGosci].getNazwa())));
}

void MainWindow::pokazSzybkiMecz()
{
    ui->ekranyStackedWidget->setCurrentWidget(ui->szybkiMeczPage);
}

void MainWindow::pokazMenu()
{
    ui->ekranyStackedWidget->setCurrentWidget(ui->menuPage);
}

void MainWindow::pokazLige()
{
    ui->ekranyStackedWidget->setCurrentWidget(ui->ligaPage);
}

void MainWindow::przygotujDruzyny()
{
    CWczytywaczDruzyn wczytywacz;
    druzyny = wczytywacz.wczytaj(":/data/druzyny.json");
}

void MainWindow::odswiezTabele()
{
    if (!liga)
    {
        return;
    }

    auto kolejnosc = liga->getKolejnoscTabeli();

    for (std::size_t i = 0; i < druzyny.size(); ++i) {
        std::size_t indeks = kolejnosc[i];
        auto statystyki = liga->getStatystyki(indeks);
        int wiersz = static_cast<int>(i);

        ui->tabelaLigiWidget->setItem(
            wiersz, 0,
            new QTableWidgetItem(QString::number(i + 1)));

        ui->tabelaLigiWidget->setItem(
            wiersz, 1,
            new QTableWidgetItem(QString::fromStdString(druzyny[indeks].getNazwa())));

        ui->tabelaLigiWidget->setItem(
            wiersz, 2,
            new QTableWidgetItem(QString::number(statystyki.rozegrane)));

        ui->tabelaLigiWidget->setItem(
            wiersz, 3,
            new QTableWidgetItem(QString::number(statystyki.punkty)));

        ui->tabelaLigiWidget->setItem(
            wiersz, 4,
            new QTableWidgetItem(QString::number(statystyki.bramkiZdobyte)));

        ui->tabelaLigiWidget->setItem(
            wiersz, 5,
            new QTableWidgetItem(QString::number(statystyki.bramkiStracone)));

        ui->tabelaLigiWidget->setItem(
            wiersz, 6,
            new QTableWidgetItem(QString::number(statystyki.roznicaBramek)));
    }
}

void MainWindow::rozegrajMeczLigi()
{
    if (!liga || !liga->czySaMecze())
    {
        return;
    }
    std::random_device zrodlo;
    unsigned int ziarno = zrodlo();
    liga->rozegrajNastepnyMecz(ziarno);
    auto wynik = liga->getOstatniWynik();
    if (wynik)
    {
        ui->ostatniWynikLabel->setText(
            QString("%1  %2 : %3  %4")
                .arg(QString::fromStdString(druzyny[wynik->gospodarze].getNazwa()))
                .arg(wynik->goleGospodarzy)
                .arg(wynik->goleGosci)
                .arg(QString::fromStdString(druzyny[wynik->goscie].getNazwa())));
    }
    odswiezTabele();
    ui->nastepnyMeczButton->setEnabled(liga->czySaMecze());
}