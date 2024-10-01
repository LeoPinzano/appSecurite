#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qpushbutton.h"
#include "qstackedwidget.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showRSAPage();
    void showAESPage();
    void showShaPage();
    void generateRSA();
    void encryptRSA();
    void decryptRSA();
    void calcSha();
    void calcFileSha();
    void generateAES();
    void encryptAES();
    void decryptAES();

private:
    Ui::MainWindow *ui;
    QPushButton *RSAbtn;
    QPushButton *AESbtn;
    QPushButton *SHA256btn;
    QStackedWidget *stackedWidget;
};
#endif // MAINWINDOW_H
