 # AppSécurité
Bienvenue sur le Projet Température en C++ avec l'utilisation de la libraire Cryptopp

## Dépendances
>[!WARNING]
>Lien pour télécharger la librairie  [Cryptopp](https://github.com/weidai11/cryptopp/releases)
>et  [CryptoCiel](https://github.com/LeoPinzano/CryptoCiel.git)
## Mode d'emploi
>[!CAUTION]
 >Assurer vous de bien avoir importer les librairies sinon voir **Compilation des librairies (ci-dessous)**
 
 1. Clonez ce dépôt sur votre machine locale :
  ```bash
   git clone https://github.com/LeoPinzano/appSecurite.git
```
2. Compilez les projets
### RSA
- Lorsque vous cliquez sur **Généner une paire de clés**, vous allez devoir séléctionner votre répertoire où vous voulez que vos clés soit stockées. Vos clés publique et privé sont sous la forme (**public_key.key**; **private_key.key**)
- Lorsque vous cliquez **Chiffrer un fichier**, vous avez le choix entre **Chiffrer un message** ou **Chiffrer un fichier**
  1. Vous pouvez mettre un message et ce dernier va être chiffrer dans un fichier en *.crypt*
  2. Vous pouvez chiffrer un fichier de votre choix
- Lorsque vous cliquez **Déchiffrer un fichier**, vous pouvez Séléctionnez **public_key.key**
  
  ### AES256
- Lorsque vous cliquez sur **Généner une clé secrète**, vous pouvez séléctionner votre répertoire où vous voulez que vos clés soit stockées. Votre clé secrète sous la forme (**aes_key.key**)
- Lorsque vous cliquez sur **Chiffrer un fichier**, vous séléctionnez votre fichier à chiffrer puis ensuite vous pouvez séléctionnez votre clé secrète **aes_key.key** (Votre Fichier sera chiffré en *.enc*)
-Lorsque vous cliquez sur **Déchiffrer un fichier**, vous pouvez Séléctionnez **public_key.key**

### SHA256
- Lorsque vous cliquez sur **Obtenir le hash d'une chaîne de caractère dans un fichier**, vous pouvez lire le hash contenu dans un fichier
- Lorsque vous cliquez sur **Obtenir le hash d'un fichier**, vous pouvez lire du fichier

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

 ## Importer des biliothèques sur QT :
1. Ouvrez **appSecurite.pro**
2. Faites clic-droit sur **appSecurite[main]** --> **Ajouter une Bibliothèque**
3. Cochez **Bibliothèque externe** puis **Suivant**
4. Assurez vous de bien avoir mis le type de bibliothèque en **Windows (*.lib lib* a)**
5. Cochez **Bibliothèque Statique**
6. Dans **Fichier de Bibliothèque** mettez votre fichier en *.lib*  qui est dans le chemin d'accès **\Cryptopp\x64\Release**
7. Dans **Chemin d'inclusion** Vous devez selectionnez l'endroit où son stocké vos fichiers **Header** en *.h*
8. Faites de même pour la libraire **CryptoCiel**
