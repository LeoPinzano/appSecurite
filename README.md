 # AppSécurité
Bienvenue sur le Projet Température en C++ avec l'utilisation de la libraire Cryptopp

## Dépendance
Lien pour télécharger la librairie  [Cryptopp](https://github.com/weidai11/cryptopp/releases)

## Mode d'emploi
 1. Clonez ce dépôt sur votre machine locale :
  ```bash
   git clone https://github.com/LeoPinzano/appSecurite.git
```
 ### Compilation des librairies :
1. Vous aller devoir d'abord compiler la librairie Cryptopp :

```bash
git clone https://github.com/weidai11/cryptopp.git
```
2. Ouvrez **cryptlib.vcxproj**
3. Faites clic-droit sur **cryptlib** --> **Propriétés**
4. Choisissez **Bibliothèque Statique.lib** ![Capture d’écran 2024-10-01 170642](https://github.com/user-attachments/assets/f9c8962e-1a0e-4b1c-9ff9-60725b2322fa)
5. Puis ensuite allez sur ***C/C++>Génération de code>Bibliothèque Runtime*** puis Séléctionnez **DLL Multithread (/MD)** ![Capture d’écran 2024-10-01 171223](https://github.com/user-attachments/assets/4d62b100-5a08-4a8c-9802-8ade9b6189a6)
6. Faites clic-droit sur **cryptlib** --> **Générér**
