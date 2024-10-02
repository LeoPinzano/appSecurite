 # AppSécurité
Bienvenue sur le Projet Température en C++ avec l'utilisation de la libraire Cryptopp

## Dépendances
>[!CAUTION]
>Lien pour télécharger la librairie  [Cryptopp](https://github.com/weidai11/cryptopp/releases)
>et  [CryptoCiel](https://github.com/LeoPinzano/CryptoCiel.git)

 ## Compilation des librairies :
#### Cryptopp
1. Vous aller devoir d'abord compiler la librairie Cryptopp :
```bash
git clone https://github.com/weidai11/cryptopp.git
```
2. Ouvrez **cryptlib.vcxproj**
3. Faites clic-droit sur **cryptlib** --> **Propriétés**
4. Choisissez **Bibliothèque Statique.lib** ![Capture d’écran 2024-10-01 170642](https://github.com/user-attachments/assets/f9c8962e-1a0e-4b1c-9ff9-60725b2322fa)
5. Puis ensuite allez sur ***C/C++>Génération de code>Bibliothèque Runtime*** puis Séléctionnez **DLL Multithread (/MD)** ![Capture d’écran 2024-10-01 171223](https://github.com/user-attachments/assets/4d62b100-5a08-4a8c-9802-8ade9b6189a6)
6. Faites clic-droit sur **cryptlib** --> **Générér**
7. Vous allez normalement trouver votre fichier en *.lib*  sur le chemin d'accès **\cryptopp\x64\Output\Release**
#### CryptoCiel 
1. Vous aller devoir d'abord compiler la librairie CryptoCiel :
```bash
git clone https://github.com/PierreViland/CryptoCiel.git
```
2. Ouvrez **cryptoCielTest.sln**
3. Faites clic-droit sur **cryptoCielTest** --> **Propriétés**
4. Choisissez **Bibliothèque Statique.lib** ![Capture d’écran 2024-10-01 170642](https://github.com/user-attachments/assets/f9c8962e-1a0e-4b1c-9ff9-60725b2322fa)
5. Puis ensuite allez sur ***C/C++>Génération de code>Bibliothèque Runtime*** puis Séléctionnez **DLL Multithread (/MD)** ![Capture d’écran 2024-10-01 171223](https://github.com/user-attachments/assets/4d62b100-5a08-4a8c-9802-8ade9b6189a6)
6. Faites clic-droit sur **cryptoCielTest** --> **Générér**
7. Vous allez normalement trouver votre fichier en *.lib*  sur le chemin d'accès **\CryptoCiel\x64\Release**

## Mode d'emploi
 1. Clonez ce dépôt sur votre machine locale :
  ```bash
   git clone https://github.com/LeoPinzano/appSecurite.git
```
### RSA
-
-
-
### AES256
-
-
-

### Hash
-
-
