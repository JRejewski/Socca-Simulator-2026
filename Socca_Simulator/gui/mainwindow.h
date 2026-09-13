#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "../src/druzyny/druzyna.h"
#include <optional>
#include "../src/rozgrywki/liga.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Główne okno aplikacji Socca Simulator.
 *
 * MainWindow odpowiada za całą warstwę graficzną programu: wczytanie
 * drużyn z zasobu JSON, przełączanie pomiędzy ekranami (menu, szybki
 * mecz, liga) za pomocą wewnętrznego QStackedWidget, obsługę symulacji
 * pojedynczego szybkiego meczu oraz prowadzenie i wyświetlanie
 * rozgrywek ligowych wraz z tabelą ligową.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Tworzy główne okno aplikacji.
     *
     * Konfiguruje widżety interfejsu, wczytuje drużyny (przygotujDruzyny()),
     * inicjalizuje rozgrywki ligowe wraz z terminarzem, wypełnia listy
     * wyboru drużyn oraz podłącza sygnały przycisków do odpowiednich
     * metod obsługi. Jeżeli wczytanie drużyn się nie powiedzie,
     * wyświetla komunikat o błędzie i blokuje centralny widżet okna.
     *
     * @param parent Widżet nadrzędny (opcjonalny, zgodnie z konwencją Qt).
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Niszczy główne okno i zwalnia zasoby interfejsu użytkownika.
     */
    ~MainWindow() override;

private:
    Ui::MainWindow *ui; ///< Wskaźnik na wygenerowany przez Qt Designer interfejs okna.

    /**
     * @brief Obsługuje symulację szybkiego meczu wybranego przez użytkownika.
     *
     * Pobiera wybrane w polach kombi drużyny gospodarzy i gości,
     * sprawdza poprawność wyboru (obie drużyny muszą być wybrane
     * i muszą się różnić), a następnie symuluje mecz (Cmecz) i wypisuje
     * wynik w etykiecie wynikowej.
     */
    void symulujMecz();

    /**
     * @brief Przełącza widok na ekran szybkiego meczu.
     */
    void pokazSzybkiMecz();

    /**
     * @brief Przełącza widok na ekran menu głównego.
     */
    void pokazMenu();

    /**
     * @brief Przełącza widok na ekran rozgrywek ligowych.
     */
    void pokazLige();

    /**
     * @brief Odświeża zawartość tabeli ligowej w interfejsie.
     *
     * Pobiera z liga aktualną kolejność drużyn oraz ich statystyki
     * i uzupełnia nimi wiersze tabelaLigiWidget. Jeżeli liga nie
     * została jeszcze utworzona, metoda nie robi nic.
     */
    void odswiezTabele();

    /**
     * @brief Rozgrywa kolejny mecz bieżącej edycji ligi.
     *
     * Jeżeli liga nie istnieje lub nie ma już meczów do rozegrania,
     * metoda nie robi nic. W przeciwnym razie symuluje kolejny mecz
     * terminarza, wyświetla jego wynik, odświeża tabelę ligową
     * i uaktualnia dostępność przycisku kolejnego meczu.
     */
    void rozegrajMeczLigi();

    std::vector<CDruzyna> druzyny; ///< Wszystkie drużyny wczytane z zasobu JSON.

    /**
     * @brief Wczytuje drużyny z zasobu JSON do pola druzyny.
     *
     * Korzysta z CWczytywaczDruzyn do wczytania danych z zasobu
     * ":/data/druzyny.json".
     *
     * @throws std::runtime_error Gdy wczytywanie danych drużyn się nie powiedzie.
     */
    void przygotujDruzyny();

    std::optional<CLiga> liga; ///< Bieżąca edycja rozgrywek ligowych (jeśli drużyny zostały poprawnie wczytane).
};
#endif // MAINWINDOW_H
