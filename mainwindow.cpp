#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to their respective slots
    connect(ui->RSAKeyBtn, &QPushButton::clicked, this, &MainWindow::generateKey);
    connect(ui->RSAencryptBtn, &QPushButton::clicked, this, &MainWindow::encryptFile);
    connect(ui->RSAdecryptBtn, &QPushButton::clicked, this, &MainWindow::decryptFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}
