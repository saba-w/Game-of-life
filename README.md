**Jeu de la vie**
========

***

## Introduction  
--------

Ceci est mon depot pour le projet de Tech dev sur le Jeu de la vie.  

Le Jeu de la vie est un automate cellulaire imaginé par John Horton Conway en 1970 et qui est probablement le plus connu de tous les automates cellulaires.  
Le code que j'ai écrit vous permet de "jouer" avec 8 différents grilles qui se trouve dans le repertoires `grilles`.  
Les régles sont asser simple. Le "jeu" se déroule sur une grille a 2 dimension dont les cases qu'on appelle "cellules" peuvent prendre 2 états distincts: "vivante" "morte".  
A chaque étape, l'évolution d'une cellule est déterminer par létat de ses huit voisines de la facon suivante:
  - Une cellule morte possédant exactement 3 voisines vivantes devient vivante.
  - Une cellule vivante possédant 2 ou 3 voisines vivantes reste vivantes, sinon elle meurt.

Voici une exemple:
La configuration ![](https://upload.wikimedia.org/wikipedia/commons/8/8a/Gol-blinker1.png) donne a l'étape suivant la configuration ![](https://upload.wikimedia.org/wikipedia/commons/a/a0/Gol-blinker2.png) qui va ensuite redonner la 1er configuration.  
 
On l'appelle la grille clignotant et c'est la grille1 qui se trouve dans le répertoire `grilles` de mon depot.  

## Different version du jeu au cours du semestre

### Les étiquettes  

v.x.y : 
  - x correspand au nombre de niveau (1,...,5)  
  - y correspand au nombre de la version du niveau x, des modification a l'interieure de cet niveau x
		
    
Exemple : v.1.1 = 2éme version du travail réalisé pour le niveau 1 (correction sur la touche `n`)

>*Version 1* 

  * Clonage du code source et programmation des fonctions alloue_grille, libere_grille
  * Programmation pour generer une nouvelle grille, la touche `n`.  
  * La documentation doxygen ainsi que le makefile ont etait ecrit lors de la version 1.0
   
>*Version 2* 
 
  * Programmation pour faire le calcul du voisinage non-cyclique, touche `c`  
  * Programmation pour faire le calcul du vieillissement, touche `v`  
  * Affichage du temps d'evolution ainsi que l'activation/desactivation du mode cyclique et du vieillissement  

>*Version 3*
  * Programmation des cellules "non-viables"
  * Repartition du code en repertoires separer

>*Version 4*
  * Programmation de l'interface graphique avec cairo
  * Ajout de la possibiliter de compiler en mode graphique: `make` et en mode texte: `make MODE=TEXTE`

>*Version 5*
  * Programmation pour tester l'oscillation d'une grille, touche `o`
  * Ajout d'une librairie libjeu.a

## Structures des fichiers
--------

- src contient toutes les fichiers sources (*.c)
- include contient toutes les en-tetes de fonctions et structures du programme (*.h)
- grilles contient l'ensemble des grilles disponibles

## Commandes importantes
--------

**Compiler le programme**

`make`  

Le fichier exécutable générer se trouve au chemin suivant : ./bin/main   
Par défaut, le programme est compilé en mode graphique. Si vous souhaiter changer vers le mode texte il faudra compiler avec `make MODE=TEXTE`. 

**Creation d'une librairie** 

`make lib` 

La librairie libjeu.a sera creer et contiendra la gestion des grilles et du jeu. 
Elle sera ranger dans le repertoires `lib` lors de sa creation.

**Générer la documentation (Doxygen)**  
   
`make doc`  

Il suffit ensuite d'ouvrir le fichier /doc/html/index.html pour accéder à l'intégralité de la documentation.  
Le README ce trouve sur gitlab ainsi que la page d'acceuille de doxygen.

**Générer une archive du programme** 
   
`make dist`  

L'archive sera créé et contiendra les dossiers src/, include/ et grilles/ ainsi que le Makefile, le Doxyfile et le README.md.

**Nettoyer les artefacts de compilation**  
   
`make clean`  

La documentation, l'èxecutable, les fichiers objets et la librairie seront effacer.

## Execution 
--------

L'execution se faisant dans des repertoires different il faudra preciser le chemin pour executer le programme: 
```
./bin/main grilles/grille1.txt
``` 
La meme regle s'applique lorsqu'on veut changer de grille: 
```
grilles/grille2.txt
``` 

**Mode graphique** 

La compilation du mode graphique ce fait avec un simple `make`.  
Pour faire evoluer la grille il faut appuyer sur la barre d'entrer ou sur le clic gauche d'une souris.  
Pour changer de grille il faut appuyer sur `n` et rentrer le chemin de notre nouvelle grille.  
Pour activer le calcule du voisinage non-cyclique il suffit d'appuyer sur `c`. Pour le desactiver il faudra appuyer sur `c` a nouveau.  
Pour activer le vieillissement c'est la touche `v`. De meme pour le desactiver.  
Pour tester si une grille oscille ou non il faut appuyer sur `o`.  
Pour quitter le programme apuyyer sur la clic droite de votre souris.  

**Mode texte** 

La compilation du mode texte ce fait avec la commande `make MODE=TEXTE`.  
Pour faire evoluer la grille on peut appuyer sur la barre espace.  
Les touches `n`, `c`, `v` et `o` fonctionnent de la meme maniere que dans le mode graphique.  
Pour quitter le programme appuyer sur `q`.  

