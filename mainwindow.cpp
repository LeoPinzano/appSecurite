#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <RsaGestion.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to their respective slots
    connect(ui->RSAKeyBtn, &QPushButton::clicked, this, &MainWindow::generateRSA);
    connect(ui->RSAencryptBtn, &QPushButton::clicked, this, &MainWindow::encryptRSA);
    connect(ui->RSAdecryptBtn, &QPushButton::clicked, this, &MainWindow::decryptRSA);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateRSA()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        QString publicKeyFile = directory + "/public_key.key";
        QString privateKeyFile = directory + "/private_key.key";

        // Appel à la méthode generationClef pour générer et sauvegarder les clés
        RsaGestion rsaGestion;
        rsaGestion.generationClef(publicKeyFile.toStdString(), privateKeyFile.toStdString(), 2048);

        QMessageBox::information(this, tr("Clés générées"), tr("Les clés publique et privé ont été enregistrées dans le même répértoire."));
    }
}

void MainWindow::encryptRSA()
{
    QString publicKeyFile = QFileDialog::getOpenFileName(this, tr("Open Public Key"), "", tr("Key Files (*.key);;All Files (*)"));
    if (!publicKeyFile.isEmpty()) {
        QString fileToEncrypt = QFileDialog::getOpenFileName(this, tr("Select File to Encrypt"), "", tr("All Files (*)"));
        if (!fileToEncrypt.isEmpty()) {
            // Effectuer le chiffrement et sauvegarder le fichier chiffré dans le même répertoire
            QFileInfo fileInfo(fileToEncrypt);
            QString encryptedFile = fileInfo.absolutePath() + "/encrypted_" + fileInfo.fileName();
            // Sauvegarder le fichier chiffré
        }
    }
}

void MainWindow::decryptRSA()
{
    QString privateKeyFile = QFileDialog::getOpenFileName(this, tr("Open Private Key"), "", tr("Key Files (*.key);;All Files (*)"));
    if (!privateKeyFile.isEmpty()) {
        QString fileToDecrypt = QFileDialog::getOpenFileName(this, tr("Select File to Decrypt"), "", tr("All Files (*)"));
        if (!fileToDecrypt.isEmpty()) {
            // Effectuer le déchiffrement et sauvegarder le fichier déchiffré dans le même répertoire
            QFileInfo fileInfo(fileToDecrypt);
            QString decryptedFile = fileInfo.absolutePath() + "/decrypted_" + fileInfo.fileName();
            // Sauvegarder le fichier déchiffré
        }
    }
}
