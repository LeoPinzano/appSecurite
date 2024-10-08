/**
 * @file mainwindow.cpp
 * @brief Implémentation de la classe MainWindow
 * @details Ce fichier contient l'implémentation des fonctionnalités principales de l'interface utilisateur,
 * y compris la gestion des clés RSA et AES, le chiffrement et déchiffrement de fichiers, et le calcul de hashes SHA-256.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <RsaGestion.h>
#include <HashGestion.h>
#include <AesGestion.h>

RsaGestion rsaGestion;
HashGestion hashGestion;
AesGestion aesGestion;

/**
 * @brief Constructeur de MainWindow
 * @param parent Pointeur vers le widget parent
 * @details Initialise l'interface utilisateur, demande à l'utilisateur de sélectionner un répertoire de base,
 * crée les sous-répertoires nécessaires et configure les connexions des boutons.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Charger le répertoire de base depuis les paramètres
    QSettings settings("VotreOrganisation", "VotreApplication");
    baseDirectory = settings.value("baseDirectory").toString();

    // Si le répertoire n'est pas défini, demander à l'utilisateur
    if (baseDirectory.isEmpty()) {
        baseDirectory = QFileDialog::getExistingDirectory(this, tr("Sélectionnez le répertoire de base"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if (baseDirectory.isEmpty()) {
            QMessageBox::warning(this, tr("Aucun répertoire sélectionné"), tr("Aucun répertoire sélectionné. Fermeture de l'application."));
            QCoreApplication::quit();
            return;
        }

        // Sauvegarder le répertoire choisi dans les paramètres
        settings.setValue("baseDirectory", baseDirectory);
    }

    // Créer les sous-répertoires si nécessaire
    QDir dir(baseDirectory);
    if (!dir.exists("cles")) {
        dir.mkpath("cles");
    }
    if (!dir.exists("chiffre")) {
        dir.mkpath("chiffre");
    }
    if (!dir.exists("dechiffre")) {
        dir.mkpath("dechiffre");
    }

    // Ajout des pages existantes au stackedWidget
    ui->stackedWidget->addWidget(ui->RSAPage);
    ui->stackedWidget->addWidget(ui->AESPage);
    ui->stackedWidget->addWidget(ui->ShaPage);

    // Connect buttons to their respective slots
    connect(ui->RSAKeyBtn, &QPushButton::clicked, this, &MainWindow::generateRSA);
    connect(ui->RSAencryptBtn, &QPushButton::clicked, this, &MainWindow::encryptRSA);
    connect(ui->RSAdecryptBtn, &QPushButton::clicked, this, &MainWindow::decryptRSA);
    connect(ui->ShaCalcBtn, &QPushButton::clicked, this, &MainWindow::calcSha);
    connect(ui->ShaCalcFileBtn, &QPushButton::clicked, this, &MainWindow::calcFileSha);
    connect(ui->AESKeyBtn, &QPushButton::clicked, this, &MainWindow::generateAES);
    connect(ui->AESencryptBtn, &QPushButton::clicked, this, &MainWindow::encryptAES);
    connect(ui->AESdecryptBtn, &QPushButton::clicked, this, &MainWindow::decryptAES);
    connect(ui->RSAbtn, &QPushButton::clicked, this, &MainWindow::showRSAPage);
    connect(ui->AESbtn, &QPushButton::clicked, this, &MainWindow::showAESPage);
    connect(ui->SHA256btn, &QPushButton::clicked, this, &MainWindow::showShaPage);
    connect(ui->changeBaseDirButton, &QPushButton::clicked, this, &MainWindow::changeBaseDirectory);
}

/**
 * @brief Destructeur de MainWindow
 * @details Libère les ressources allouées pour l'interface utilisateur.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Affiche la page RSA dans l'interface
 * @details Change l'index du QStackedWidget pour afficher la page dédiée aux opérations RSA.
 */
void MainWindow::showRSAPage() {
    ui->stackedWidget->setCurrentIndex(0);
}

/**
 * @brief Affiche la page AES dans l'interface
 * @details Change l'index du QStackedWidget pour afficher la page dédiée aux opérations AES.
 */
void MainWindow::showAESPage() {
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Affiche la page Sha256 dans l'interface
 * @details Change l'index du QStackedWidget pour afficher la page dédiée aux opérations Sha256.
 */
void MainWindow::showShaPage() {
    ui->stackedWidget->setCurrentIndex(2);
}

/**
 * @brief Change le répertoire de base de l'application
 * @details Cette fonction permet à l'utilisateur de sélectionner un nouveau répertoire de base pour l'application.
 * Elle met à jour la variable baseDirectory, sauvegarde le nouveau chemin dans les paramètres de l'application,
 * crée les sous-répertoires nécessaires (cles, chiffre, dechiffre) dans le nouveau répertoire,
 * et informe l'utilisateur du changement.
 *
 * @note Cette fonction utilise QSettings pour sauvegarder le nouveau répertoire de base de manière persistante.
 * @note Les sous-répertoires sont créés automatiquement si ils n'existent pas déjà dans le nouveau répertoire.
 */
void MainWindow::changeBaseDirectory()
{
    QString newDirectory = QFileDialog::getExistingDirectory(this, tr("Sélectionnez le nouveau répertoire de base"), baseDirectory, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!newDirectory.isEmpty()) {
        baseDirectory = newDirectory;
        QSettings settings("VotreOrganisation", "VotreApplication");
        settings.setValue("baseDirectory", baseDirectory);

        // Créer les sous-répertoires dans le nouveau répertoire
        QDir dir(baseDirectory);
        if (!dir.exists("cles")) {
            dir.mkpath("cles");
        }
        if (!dir.exists("chiffre")) {
            dir.mkpath("chiffre");
        }
        if (!dir.exists("dechiffre")) {
            dir.mkpath("dechiffre");
        }

        QMessageBox::information(this, tr("Répertoire de base modifié"), tr("Le nouveau répertoire de base a été défini et sera utilisé à partir de maintenant."));
    }
}

/**
 * @brief Génère une nouvelle paire de clés RSA
 * @details Crée une nouvelle paire de clés RSA (publique et privée) et les enregistre dans le répertoire de base.
 * Utilise une taille de clé de 2048 bits. Affiche un message de confirmation à l'utilisateur.
 */
void MainWindow::generateRSA()
{
    QString publicKeyFile = baseDirectory + "/cles/cle_pub.key";
    QString privateKeyFile = baseDirectory + "/cles/cle_priv.key";
    try {
        rsaGestion.generationClef(publicKeyFile.toStdString(), privateKeyFile.toStdString(), 2048);
        QMessageBox::information(this, tr("Clés générées"), tr("Les clés publique et privée ont été enregistrées dans le répertoire:\n") + baseDirectory + "/cles/");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Erreur de génération des clés"), tr("Impossible de générer les clés RSA : ") + QString(e.what()));
    }
}

/**
 * @brief Chiffre un message ou un fichier avec RSA
 * @details Offre à l'utilisateur le choix entre chiffrer un message texte ou un fichier.
 * Pour un message, demande la saisie du texte et le chiffre.
 * Pour un fichier, permet à l'utilisateur de sélectionner le fichier à chiffrer.
 * Utilise la clé publique RSA stockée dans le répertoire de base.
 * Enregistre le résultat chiffré dans le sous-répertoire 'chiffre'.
 */
void MainWindow::encryptRSA()
{
    QStringList options;
    options << tr("Chiffrer un message") << tr("Chiffrer un fichier (recommandé pour clé AES ou Hash)");
    bool ok;
    QString choice = QInputDialog::getItem(this, tr("Choix de chiffrement"), tr("Que voulez-vous chiffrer ?"), options, 0, false, &ok);

    if (!ok || choice.isEmpty()) {
        QMessageBox::warning(this, tr("Opération annulée"), tr("Aucune option sélectionnée."));
        return;
    }

    RsaGestion rsaGestion;

    if (choice == tr("Chiffrer un message")) {
        QString message = QInputDialog::getText(this, tr("Entrer un message"), tr("Message:"), QLineEdit::Normal, "", &ok);
        if (!ok || message.isEmpty()) {
            QMessageBox::warning(this, tr("Opération annulée"), tr("Aucun message saisi."));
            return;
        }

        QString publicKeyFile = baseDirectory + "/cles/cle_pub.key";
        if (!QFile::exists(publicKeyFile)) {
            QMessageBox::critical(this, tr("Erreur"), tr("Fichier de clé publique non trouvé : ") + publicKeyFile);
            return;
        }

        try {
            rsaGestion.chargementClefsPublic(publicKeyFile.toStdString());
        } catch (const std::exception& e) {
            QMessageBox::critical(this, tr("Erreur"), tr("Impossible de charger la clé publique : ") + QString(e.what()));
            return;
        }

        QString encryptedFile = baseDirectory + "/chiffre/" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + "_message.crypt";
        try {
            rsaGestion.chiffreDansFichier(message.toStdString(), encryptedFile.toStdString());
            QMessageBox::information(this, tr("Message chiffré"), tr("Message chiffré enregistré vers:\n") + encryptedFile);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, tr("Erreur de chiffrement"), tr("Impossible de chiffrer le message : ") + QString(e.what()));
        }
    } else if (choice == tr("Chiffrer un fichier (recommandé pour clé AES ou Hash)")) {
        QString publicKeyFile = baseDirectory + "/cles/cle_pub.key";
        if (!QFile::exists(publicKeyFile)) {
            QMessageBox::critical(this, tr("Erreur"), tr("Fichier de clé publique non trouvé : ") + publicKeyFile);
            return;
        }

        QString fileToEncrypt = QFileDialog::getOpenFileName(this, tr("Sélection fichier"), "", tr("All Files (*)"));
        if (fileToEncrypt.isEmpty()) {
            QMessageBox::warning(this, tr("Opération annulée"), tr("Aucun fichier sélectionné."));
            return;
        }

        QString encryptedFile = baseDirectory + "/chiffre/" + QFileInfo(fileToEncrypt).fileName() + ".crypt";

        try {
            rsaGestion.chargementClefsPublic(publicKeyFile.toStdString());
            rsaGestion.chiffrementFichier(fileToEncrypt.toStdString(), encryptedFile.toStdString(), true);
            QMessageBox::information(this, tr("Fichier chiffré"), tr("Fichier chiffré enregistré vers:\n") + encryptedFile);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, tr("Erreur de chiffrement"), tr("Impossible de chiffrer le fichier : ") + QString(e.what()));
        }
    }
}

/**
 * @brief Déchiffre un fichier avec RSA
 * @details Permet à l'utilisateur de sélectionner un fichier chiffré.
 * Utilise la clé privée RSA stockée dans le répertoire de base pour déchiffrer.
 * Enregistre le fichier déchiffré dans le sous-répertoire 'dechiffre'.
 */
void MainWindow::decryptRSA()
{
    QString encryptedFile = QFileDialog::getOpenFileName(this, tr("Ouvrir fichier chiffré"), "", tr("Encrypted Files (*.crypt);;All Files (*)"));
    if (!encryptedFile.isEmpty()) {
        QString privateKeyFile = baseDirectory + "/cles/cle_priv.key";
        if (!QFile::exists(privateKeyFile)) {
            QMessageBox::warning(this, tr("Erreur"), tr("Fichier de clé privée non trouvé : ") + privateKeyFile);
            return;
        }
        QString decryptedFile = baseDirectory + "/dechiffre/" + QFileInfo(encryptedFile).completeBaseName() + ".decrypt";
        try {
            RsaGestion rsaGestion;
            rsaGestion.chargementClefsPrive(privateKeyFile.toStdString());
            rsaGestion.dechiffrementFichier(encryptedFile.toStdString(), decryptedFile.toStdString(), true);
            QMessageBox::information(this, tr("Fichier déchiffré"), tr("Fichier déchiffré enregistré vers:\n") + decryptedFile);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, tr("Erreur de déchiffrement"), tr("Impossible de déchiffrer le fichier : ") + QString(e.what()));
        }
    }
}

/**
 * @brief Calcule le hash SHA-256 d'un message
 * @details Permet à l'utilisateur de sélectionner un fichier contenant le message.
 * Lit le contenu du fichier et calcule son hash SHA-256.
 * Affiche le résultat du hash à l'utilisateur.
 */
void MainWindow::calcSha()
{
    QString fileToHash = QFileDialog::getOpenFileName(this, tr("Selectionnez le message à hasher"), "", tr("All Files (*)"));
    if (!fileToHash.isEmpty()) {
        QFile file(fileToHash);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray fileData = file.readAll();
            file.close();
            try {
                std::string hashResult = hashGestion.CalculateSHA256(fileData.toStdString());
                QMessageBox::information(this, tr("Hash SHA-256"), tr("Le SHA256 de votre message est:\n") + QString::fromStdString(hashResult));
            } catch (const std::exception& e) {
                QMessageBox::critical(this, tr("Erreur de calcul du hash"), tr("Impossible de calculer le hash : ") + QString(e.what()));
            }
        } else {
            QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier message."));
        }
    }
}

/**
 * @brief Calcule le hash SHA-256 d'un fichier
 * @details Permet à l'utilisateur de sélectionner un fichier.
 * Calcule le hash SHA-256 du fichier entier.
 * Affiche le résultat du hash à l'utilisateur.
 */
void MainWindow::calcFileSha()
{
    QString fileToHash = QFileDialog::getOpenFileName(this, tr("Selectionnez le fichier à hasher"), "", tr("All Files (*)"));
    if (!fileToHash.isEmpty()) {
        try {
            std::string hashResult = hashGestion.CalculateFileSHA256(fileToHash.toStdString());
            if (!hashResult.empty()) {
                QMessageBox::information(this, tr("Hash SHA-256"), tr("Le SHA256 de votre fichier est:\n") + QString::fromStdString(hashResult));
            } else {
                QMessageBox::warning(this, tr("Erreur"), tr("Impossible de calculer le hash du fichier."));
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, tr("Erreur de calcul du hash"), tr("Impossible de calculer le hash : ") + QString(e.what()));
        }
    }
}

/**
 * @brief Génère une nouvelle clé AES
 * @details Crée une nouvelle clé AES et l'enregistre dans le répertoire de base.
 * Affiche un message de confirmation à l'utilisateur avec l'emplacement de la clé.
 */
void MainWindow::generateAES()
{
    QString keyFile = baseDirectory + "/cles/cle_aes.key";
    try {
        AesGestion aesGestion;
        aesGestion.GenerateAESKey();
        aesGestion.SaveAESKeyToFile(keyFile.toStdString());
        QMessageBox::information(this, tr("Clé AES générée"), tr("Clé AES enregistrée dans le répertoire:\n") + keyFile);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Erreur de génération de clé AES"), tr("Impossible de générer la clé AES : ") + QString(e.what()));
    }
}

/**
 * @brief Chiffre un fichier avec AES
 * @details Permet à l'utilisateur de sélectionner un fichier à chiffrer.
 * Utilise la clé AES stockée dans le répertoire de base pour le chiffrement.
 * Enregistre le fichier chiffré dans le sous-répertoire 'chiffre'.
 */
void MainWindow::encryptAES()
{
    QString keyFile = baseDirectory + "/cles/cle_aes.key";
    if (!QFile::exists(keyFile)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Fichier de clé AES non trouvé : ") + keyFile);
        return;
    }
    QString fileToEncrypt = QFileDialog::getOpenFileName(this, tr("Séléctionnez le fichier à chiffrer"), "", tr("All Files (*)"));
    if (!fileToEncrypt.isEmpty()) {
        QString encryptedFile = baseDirectory + "/chiffre/" + QFileInfo(fileToEncrypt).fileName() + ".enc";
        try {
            AesGestion aesGestion;
            aesGestion.LoadAESKeyFromFile(keyFile.toStdString());
            aesGestion.EncryptFileAES256(fileToEncrypt.toStdString(), encryptedFile.toStdString());
            QMessageBox::information(this, tr("Fichier chiffré"), tr("Fichier chiffré enregistré sous:\n") + encryptedFile);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, tr("Erreur de chiffrement AES"), tr("Impossible de chiffrer le fichier : ") + QString(e.what()));
        }
    }
}

/**
 * @brief Déchiffre un fichier avec AES
 * @details Permet à l'utilisateur de sélectionner un fichier chiffré.
 * Utilise la clé AES stockée dans le répertoire de base pour le déchiffrement.
 * Enregistre le fichier déchiffré dans le sous-répertoire 'dechiffre'.
 */
void MainWindow::decryptAES()
{
    QString keyFile = baseDirectory + "/cles/cle_aes.key";
    if (!QFile::exists(keyFile)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Fichier de clé AES non trouvé : ") + keyFile);
        return;
    }
    QString encryptedFile = QFileDialog::getOpenFileName(this, tr("Ouvrir le fichier chiffre"), "", tr("Encrypted Files (*.enc);;All Files (*)"));
    if (!encryptedFile.isEmpty()) {
        QString decryptedFile = baseDirectory + "/dechiffre/" + QFileInfo(encryptedFile).completeBaseName();
        try {
            AesGestion aesGestion;
            aesGestion.LoadAESKeyFromFile(keyFile.toStdString());
            aesGestion.DecryptFileAES256(encryptedFile.toStdString(), decryptedFile.toStdString());
            QMessageBox::information(this, tr("Fichier déchiffré"), tr("Fichier déchiffré enregistré sous:\n") + decryptedFile);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, tr("Erreur de déchiffrement AES"), tr("Impossible de déchiffrer le fichier : ") + QString(e.what()));
        }
    }
}
