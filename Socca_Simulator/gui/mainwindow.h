#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "../src/druzyny/druzyna.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    void symulujMecz();
    void pokazSzybkiMecz();
    void pokazMenu();

    std::vector<CDruzyna> druzyny;

    void przygotujDruzyny();
};
#endif // MAINWINDOW_H
