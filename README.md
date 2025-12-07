# Game of Life

**Projet POO - Groupe 6**  
Elliot CAZAJOUS REY, Misha DOPRE, Gabriel BUTAUD

<img src="https://i.imgur.com/NpD4pUu.png" alt="Jeu de la Vie - Capture d'écran" width="75%" />

## Description

Implémentation en C++ du Jeu De La Vie de John Conway. Le programme simule l'évolution d'une population de cellules selon certaines règles, avec deux extensions bonus :

- **Grille torique** : les bords sont connectés  
- **Cellules obstacles** : cellules immuables qui ne changent jamais d'état (paramétrables facilement)

## Installation

### Méthode 1 : Télécharger la release (Pas de compilation requise)

1. Télécharger `JeuDeLaVie.zip` depuis les [Releases](https://github.com/ZiKorT/Game-Of-Life/releases)  
2. Extraire le contenu du fichier `.zip`  
3. Lancer via les fichiers `.bat` :  
   - `LauncherGraphique.bat` : Mode graphique  
   - `LauncherConsole.bat` : Mode console (résultats dans le dossier "input.txt_out")  
   - `LauncherTests.bat` : Tests unitaires

Ne pas lancer directement le `.exe`, utiliser les launchers.

### Méthode 2 : Compilation manuelle

**Prérequis :** CMake 3.17+, compilateur C++20, Git

```bash
git clone https://github.com/ZiKorT/Game-Of-Life.git
cd Game-Of-Life
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

**Exécution :**
```bash
# Depuis le dossier build
.\Release\Game_Of_Life.exe ..\input.txt 1 # Mode graphique
.\Release\Game_Of_Life.exe ..\input.txt 0 # Mode console
.\Release\RunTests.exe # Tests unitaires

# Ou depuis la racine du projet
.\build\Release\Game_Of_Life.exe .\input.txt 1
.\build\Release\RunTests.exe
```

## Format du fichier d'entrée ("input.txt")

| Valeur | Signification |
|--------|---------------|
| `0`    | Cellule morte |
| `1`    | Cellule vivante |
| `2`    | Obstacle (immuable) |

## Contrôles (Mode Graphique)

| Touche  | Action        |
|---------|---------------|
| `Espace`| Pause / Reprise |
| `↑`     | Accélérer     |
| `↓`     | Ralentir      |

## Règles de Conway

- Cellule morte + 3 voisines vivantes -> devient vivante  
- Cellule vivante + 2 ou 3 voisines -> reste vivante  
- Sinon -> la cellule meurt  
- Les obstacles (en rouge) ne changent jamais d'état
