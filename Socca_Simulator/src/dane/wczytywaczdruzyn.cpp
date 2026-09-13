#include "wczytywaczdruzyn.h"
#include <QFile>
#include <stdexcept>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QSet>
#include <cmath>

namespace {

QString wymaganyTekst(const QJsonObject& obiekt, const QString& klucz)
{
    const auto wartosc = obiekt.value(klucz);
    if (!wartosc.isString() || wartosc.toString().trimmed().isEmpty())
        throw std::runtime_error(("Brak lub pusty tekst: " + klucz).toStdString());
    return wartosc.toString().trimmed();
}

int atrybut(const QJsonObject& obiekt, const QString& klucz)
{
    const auto wartosc = obiekt.value(klucz);
    const double liczba = wartosc.toDouble();
    if (!wartosc.isDouble() || !std::isfinite(liczba)
        || liczba < 1 || liczba > 100 || std::floor(liczba) != liczba)
        throw std::runtime_error(("Wymagana liczba calkowita 1-100: " + klucz).toStdString());
    return static_cast<int>(liczba);
}

QJsonObject obiektGracza(const QJsonValue& wartosc, QSet<QString>& identyfikatory)
{
    if (!wartosc.isObject())
        throw std::runtime_error("Zawodnik musi byc obiektem.");
    const auto obiekt = wartosc.toObject();
    const auto id = wymaganyTekst(obiekt, "id");
    if (identyfikatory.contains(id))
        throw std::runtime_error(("Powtorzone ID zawodnika: " + id).toStdString());
    identyfikatory.insert(id);
    return obiekt;
}

CPilkarz wczytajPilkarza(const QJsonValue& wartosc, QSet<QString>& identyfikatory)
{
    const auto p = obiektGracza(wartosc, identyfikatory);
    return CPilkarz{
        wymaganyTekst(p, "imie").toStdString(),
        wymaganyTekst(p, "nazwisko").toStdString(),
        atrybut(p, "celnosc"), atrybut(p, "fizycznosc"), atrybut(p, "charyzma"),
        atrybut(p, "szybkosc"), atrybut(p, "technika"), atrybut(p, "defensywa")};
}

CBramkarz wczytajBramkarza(const QJsonValue& wartosc, QSet<QString>& identyfikatory)
{
    const auto p = obiektGracza(wartosc, identyfikatory);
    return CBramkarz{
        wymaganyTekst(p, "imie").toStdString(),
        wymaganyTekst(p, "nazwisko").toStdString(),
        atrybut(p, "celnosc"), atrybut(p, "fizycznosc"), atrybut(p, "charyzma"),
        atrybut(p, "pozycjonowanie"), atrybut(p, "inteligencja"), atrybut(p, "parady")};
}

}

CWczytywaczDruzyn::CWczytywaczDruzyn() {}

std::vector<CDruzyna> CWczytywaczDruzyn::wczytaj(
    const QString& sciezka) const
{
    QFile plik{sciezka};
    if (!plik.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Nie mozna otworzyc pliku druzyn.");
    }
    QJsonParseError blad;
    QJsonDocument dokument =
        QJsonDocument::fromJson(plik.readAll(), &blad);

    if (blad.error != QJsonParseError::NoError)
    {
        throw std::runtime_error("Niepoprawny format JSON.");
    }

    if (!dokument.isObject())
    {
        throw std::runtime_error("Glowny element JSON musi byc obiektem.");
    }

    QJsonObject korzen = dokument.object();

    if (!korzen.value("wersjaFormatu").isDouble()
        || korzen.value("wersjaFormatu").toDouble() != 1)
        throw std::runtime_error("Obslugiwana wersjaFormatu to 1.");

    if (!korzen.value("druzyny").isArray())
    {
        throw std::runtime_error("Brakuje druzyn lub są niepoprawne");
    }

    QJsonArray zespoly = korzen.value("druzyny").toArray();
    if (zespoly.size() < 2)
        throw std::runtime_error("Wymagane sa co najmniej dwie druzyny.");

    std::vector<CDruzyna> druzyny;
    QSet<QString> idDruzyn, idGraczy, nazwyDruzyn;
    for (qsizetype i = 0; i < zespoly.size(); ++i)
    {
        if (!zespoly.at(i).isObject())
        {
            throw std::runtime_error("Drużyna nie jest obiektem");
        }
        QJsonObject zespol = zespoly.at(i).toObject();
        if (!zespol.value("nazwa").isString())
        {
            throw std::runtime_error("Niepoprawna nazwa drużyny");
        }
        QString nazwa = zespol.value("nazwa").toString().trimmed();
        if (nazwa.isEmpty())
            throw std::runtime_error("Nazwa druzyny nie moze byc pusta.");

        const auto id = wymaganyTekst(zespol, "id");
        if (idDruzyn.contains(id) || nazwyDruzyn.contains(nazwa.toCaseFolded()))
            throw std::runtime_error(("Powtorzona druzyna: " + nazwa).toStdString());
        idDruzyn.insert(id);
        nazwyDruzyn.insert(nazwa.toCaseFolded());

        try
        {
            if (!zespol.value("pilkarze").isArray())
                throw std::runtime_error("Brak tablicy pilkarze.");
            const auto p = zespol.value("pilkarze").toArray();
            if (p.size() != 5)
                throw std::runtime_error("Wymaganych jest dokladnie 5 pilkarzy.");

            std::array<CPilkarz, 5> sklad{
                wczytajPilkarza(p.at(0), idGraczy),
                wczytajPilkarza(p.at(1), idGraczy),
                wczytajPilkarza(p.at(2), idGraczy),
                wczytajPilkarza(p.at(3), idGraczy),
                wczytajPilkarza(p.at(4), idGraczy)};
            auto bramkarz = wczytajBramkarza(zespol.value("bramkarz"), idGraczy);
            druzyny.emplace_back(nazwa.toStdString(), sklad, bramkarz);
        }
        catch (const std::runtime_error& bladDanych)
        {
            throw std::runtime_error(nazwa.toStdString() + ": " + bladDanych.what());
        }
    }

    return druzyny;
}

