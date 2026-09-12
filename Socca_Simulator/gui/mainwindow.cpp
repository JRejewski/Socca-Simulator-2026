#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include "../src/mecze/mecz.h"
#include <QString>
#include <random>
#include <QComboBox>
#include "../src/rozgrywki/liga.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    przygotujDruzyny();
    CLiga liga{druzyny};
    liga.generujTerminarz();
    qDebug() << "Liczba meczow:" << liga.czySaMecze();

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

void MainWindow::przygotujDruzyny()
{
    CPilkarz pilkarzPol{"Jan", "Kowalski", 60, 60, 60, 60, 60, 60};
    CBramkarz bramkarz{"Adam", "Nowak", 80, 80, 80, 80, 80, 80};
    std::array<CPilkarz, 5> skladPol{pilkarzPol, pilkarzPol, pilkarzPol, pilkarzPol, pilkarzPol};

    CPilkarz pilkarzNiem{"Jurgen", "Klopp", 60, 60, 60, 60, 60, 60};
    std::array<CPilkarz, 5> skladNiem{pilkarzNiem, pilkarzNiem, pilkarzNiem, pilkarzNiem, pilkarzNiem};

    CPilkarz pilkarzChor{"Ivan", "Rakitic", 70, 70, 70, 70, 70, 70};
    std::array<CPilkarz, 5> skladChor{pilkarzChor, pilkarzChor, pilkarzChor, pilkarzChor, pilkarzChor};


    CDruzyna Polska{"Polska", skladPol, bramkarz};
    CDruzyna Niemcy{"Niemcy", skladNiem, bramkarz};
    CDruzyna Chorwacja{"Chorwacja", skladChor, bramkarz};

    druzyny.push_back(Polska);
    druzyny.push_back(Niemcy);
    druzyny.push_back(Chorwacja);
}