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

    przygotujDruzyny();

    ui->tabelaLigiWidget->setRowCount(static_cast<int>(druzyny.size()));

    liga.emplace(druzyny);
    liga->generujTerminarz();

    // unsigned int ziarno{0};

    // while (liga->czySaMecze())
    // {
    //     liga->rozegrajNastepnyMecz(ziarno);
    //     ++ziarno;
    // }

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
    CPilkarz pilkarzPol{"Jan", "Kowalski", 60, 60, 60, 60, 60, 60};
    CBramkarz bramkarz{"Adam", "Nowak", 80, 80, 80, 80, 80, 80};
    std::array<CPilkarz, 5> skladPol{pilkarzPol, pilkarzPol, pilkarzPol, pilkarzPol, pilkarzPol};

    CPilkarz pilkarzNiem{"Jurgen", "Klopp", 60, 60, 60, 60, 60, 60};
    std::array<CPilkarz, 5> skladNiem{pilkarzNiem, pilkarzNiem, pilkarzNiem, pilkarzNiem, pilkarzNiem};

    CPilkarz pilkarzChor{"Ivan", "Rakitic", 70, 70, 70, 70, 70, 70};
    std::array<CPilkarz, 5> skladChor{pilkarzChor, pilkarzChor, pilkarzChor, pilkarzChor, pilkarzChor};

    CPilkarz pilkarzNig{"Tymoteusz", "Jasc00lski", 84, 57, 65, 80, 67, 78};
    std::array<CPilkarz, 5> skladNig{pilkarzNig, pilkarzNig, pilkarzNig, pilkarzNig, pilkarzNig};

    CDruzyna Polska{"Polska", skladPol, bramkarz};
    CDruzyna Niemcy{"Niemcy", skladNiem, bramkarz};
    CDruzyna Chorwacja{"Chorwacja", skladChor, bramkarz};
    CDruzyna Nigeria{"Nigeria", skladNig, bramkarz};

    druzyny.push_back(Polska);
    druzyny.push_back(Niemcy);
    druzyny.push_back(Chorwacja);
    druzyny.push_back(Nigeria);
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