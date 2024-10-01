#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <RsaGestion.h>
#include <HashGestion.h>

RsaGestion rsaGestion;
HashGestion hashGestion;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons to their respective slots
    connect(ui->RSAKeyBtn, &QPushButton::clicked, this, &MainWindow::generateRSA);
    connect(ui->RSAencryptBtn, &QPushButton::clicked, this, &MainWindow::encryptRSA);
    connect(ui->RSAdecryptBtn, &QPushButton::clicked, this, &MainWindow::decryptRSA);
    connect(ui->ShaCalcBtn, &QPushButton::clicked, this, &MainWindow::calcSha);
    connect(ui->ShaCalcFileBtn, &QPushButton::clicked, this, &MainWindow::calcFileSha);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateRSA()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Selectionner le repertoire"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty()) {
        QString publicKeyFile = directory + "/public_key.key";
        QString privateKeyFile = directory + "/private_key.key";

        // Appel à la méthode generationClef pour générer et sauvegarder les clés
        rsaGestion.generationClef(publicKeyFile.toStdString(), privateKeyFile.toStdString(), 2048);

        QMessageBox::information(this, tr("Clés générées"), tr("Les clés publique et privé ont été enregistrées dans le même répértoire."));
    }
}

void MainWindow::encryptRSA()
{
    // Demander à l'utilisateur de choisir entre chiffrer un message ou un fichier
    QStringList options;
    options << tr("Chiffrer un message") << tr("Chiffrer un fichier (recommandé pour clé AES ou Hash)");
    bool ok;
    QString choice = QInputDialog::getItem(this, tr("Choix de chiffrement"), tr("Que voulez-vous chiffrer ?"), options, 0, false, &ok);

    if (ok && !choice.isEmpty()) {
        RsaGestion rsaGestion;

        if (choice == tr("Chiffrer un message")) {
            // Chiffrer un message
            QString message = QInputDialog::getText(this, tr("Entrer un message"), tr("Message:"), QLineEdit::Normal, "", &ok);
            if (ok && !message.isEmpty()) {
                QString publicKeyFile = QFileDialog::getOpenFileName(this, tr("Séléction clé publique"), "", tr("Key Files (*.key);;All Files (*)"));
                if (!publicKeyFile.isEmpty()) {
                    // Charger la clé publique et chiffrer le message
                    rsaGestion.chargementClefsPublic(publicKeyFile.toStdString());
                    QString encryptedFile = QFileDialog::getSaveFileName(this, tr("Sauvegarde message chiffré"), "", tr("Encrypted Files (*.crypt);;All Files (*)"));
                    if (!encryptedFile.isEmpty()) {
                        rsaGestion.chiffreDansFichier(message.toStdString(), encryptedFile.toStdString());
                        QMessageBox::information(this, tr("Message chiffré"), tr("Message chiffré enregistré vers:\n") + encryptedFile);
                    }
                }
            }
        } else if (choice == tr("Chiffrer un fichier (recommandé pour clé AES ou Hash)")) {
            // Chiffrer un fichier
            QString publicKeyFile = QFileDialog::getOpenFileName(this, tr("Séléction clé publique"), "", tr("Key Files (*.key);;All Files (*)"));
            if (!publicKeyFile.isEmpty()) {
                QString fileToEncrypt = QFileDialog::getOpenFileName(this, tr("Séléction fichier"), "", tr("All Files (*)"));
                if (!fileToEncrypt.isEmpty()) {
                    QString encryptedFile = QFileDialog::getSaveFileName(this, tr("Sauvegarde fichier chiffré"), "", tr("Encrypted Files (*.crypt);;All Files (*)"));
                    if (!encryptedFile.isEmpty()) {
                        rsaGestion.chargementClefsPublic(publicKeyFile.toStdString());
                        rsaGestion.chiffrementFichier(fileToEncrypt.toStdString(), encryptedFile.toStdString(), true);
                        QMessageBox::information(this, tr("Fichier chiffré"), tr("Fichier chiffré enregistré vers:\n") + encryptedFile);
                    }
                }
            }
        }
    }
}

void MainWindow::decryptRSA()
{
    QString encryptedFile = QFileDialog::getOpenFileName(this, tr("Ouvrir fichier chiffré"), "", tr("Encrypted Files (*.crypt);;All Files (*)"));
    if (!encryptedFile.isEmpty()) {
        QString privateKeyFile = QFileDialog::getOpenFileName(this, tr("Selection clé privé"), "", tr("Key Files (*.key);;All Files (*)"));
        if (!privateKeyFile.isEmpty()) {
            QString decryptedFile = QFileDialog::getSaveFileName(this, tr("Sauvegarde fichier déchiffré"), "", tr("Decrypted Files (*.decrypt);;All Files (*)"));
            if (!decryptedFile.isEmpty()) {
                rsaGestion.chargementClefsPrive(privateKeyFile.toStdString());
                rsaGestion.dechiffrementFichier(encryptedFile.toStdString(), decryptedFile.toStdString(), true);
                QMessageBox::information(this, tr("Fichier déchiffré"), tr("Fichier déchiffré enregistré vers:\n") + decryptedFile);
            }
        }
    }
}


void MainWindow::calcSha()
{
    QString fileToHash = QFileDialog::getOpenFileName(this, tr("Select File to Hash"), "", tr("All Files (*)"));
    if (!fileToHash.isEmpty()) {
        QFile file(fileToHash);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray fileData = file.readAll();
            file.close();

            HashGestion hashGestion;
            std::string hashResult = hashGestion.CalculateSHA256(fileData.toStdString());

            QMessageBox::information(this, tr("SHA-256 Hash"), tr("The SHA-256 hash of the file is:\n") + QString::fromStdString(hashResult));
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Unable to open the file."));
        }
    }
}

void MainWindow::calcFileSha()
{
    QString fileToHash = QFileDialog::getOpenFileName(this, tr("Select File to Hash"), "", tr("All Files (*)"));
    if (!fileToHash.isEmpty()) {
        HashGestion hashGestion;
        std::string hashResult = hashGestion.CalculateFileSHA256(fileToHash.toStdString());

        if (!hashResult.empty()) {
            QMessageBox::information(this, tr("SHA-256 Hash"), tr("The SHA-256 hash of the file is:\n") + QString::fromStdString(hashResult));
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Unable to calculate the hash of the file."));
        }
    }
}
