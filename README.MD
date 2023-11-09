# Space Invaders par Romain DUHR

1. Description du jeu
1. Compilation
1. Arborescence de l'archive
1. Fichiers principaux du jeu
    1. Fichier ListeChainee
    1. Fichier ship
    1. Fichier enemies
    1. Fichier main 

## Description du jeu

Cette archive permet d'exécuter un jeu codé en c se basant sur le jeu Space Invaders sorti en 1978.
Le principe : le joueur contrôle un vaisseau vert qui se déplace en bas de la fenêtre de gauche à droite. Il peut tirer des missiles afin de tuer des ennemis représentés par des petits aliens bleus. Ces aliens se déplacent en bloc également de gauche à droite et descendent petit à petit vers le joueur s'ils arrivent à sa hauteur c'est perdu ! Les aliens peuvent également lâcher des bombes pour rendre la tâche du joueur plus difficile. Si une bombe touche un missile les 2 se détruisent. Le joueur a 3 vies s'il est touché 3 fois par des bombes alors il perd. Si le joueur tue tous les aliens alors c'est gagnés !!

Note : Le jeu s'adapte à la taille d'écran choisi dans define.h WIDTH 700 ET HEIGHT 800 sont très agréable à jouer

## Arborescence de l'archive 

* Lutins
* src
    * Graphique
    * Entities
    * Liste Chainee

Le répertoire lutins contient les sprites du jeu.  
L'ensemble du code se trouve dans le répertoire source.  
    Le répertoire Graphique inclut la librairie libgraph qui permet le bon affichage.  
    Le répertoire ListeChainee inclut les .c et .h pour l'implémentation des listes.  
    Le répertoire Entities inclut les .c et .h nécessaire à la gestion des entitées.

## Compilation 

Afin de compiler correctement l'archive il faut que la SDL1 et la librairie ttf soit correctement installée 
```
sudo apt-get upgrade
sudo apt install libsdl1.2-dev
sudo apt install libsdl-ttf2.0-dev
```
[Le package SDL](https://packages.debian.org/search?suite=default&section=all&arch=any&searchon=names&keywords=SDL+1.2)

Ensuite il vous suffira d'éxécuter **make dans le répertoire graphique** et **make dans src** puis vous pourrez lancer le jeu avec **./main dans src** 

Note : L'ensemble des fichiers .o se trouveront dans le répertoir obj

## Fichier Liste Chainee 

Vous trouverez ici la gestion des listes chainées comprenant les fonctions suivantes

```
void head_push(list_t* pL, entity_t l);
int size(list_t l);
entity_t head_pop(list_t* pL);
void pop(list_t* pL, element_t* e);
void drawList(list_t l);
void free_list(list_t* pL);
void moveEntities_x(list_t entities, int dir, int step);
void moveEntities_y(list_t entities, int dir, int step);
void updateEntitiesSprite(list_t entities, int s);
list_t pickAllowedEnemies(list_t enemies);
```

## Fichier ship 

Vous trouverez ici la gestion du vaisseau et des missiles comprenant les fonctions suivantes

```
void initShip(entity_t* ship);
void drawShip(entity_t ship, list_t missiles, int lives);
void moveShip_x(entity_t* ship, int dir);
int isCollapsing(entity_t first, entity_t second);
void checkCollision(list_t* missiles, list_t* others_);
void updateMissiles(list_t* missiles, list_t* enemies, list_t* bombs);
void shotShip(entity_t ship, list_t* missiles);
```

## Fichier enemies 

Vous trouverez ici la gestion des enemies et de leurs bombes comprenant les fonctions suivantes

```
void initEnemies(list_t* enemies);
int isEdgingEnemies(list_t enemies);
void moveEnemies(list_t enemies, int* enemiesSpeed);
list_t pickAllowedEnemies(list_t enemies);
void shotEnemies(list_t enemies, list_t* bombs);
void updateEnemies(list_t enemies, list_t* bombs, int* enemiesSpeed);
void updateBombs(list_t* bombs, entity_t* ship, int* lives);
void drawEnemies(list_t enemies, list_t bombs);
int isWiningEnemies(list_t enemies, entity_t ship);
```
## Fichier main

Vous trouverez ici la gestion du jeu en lui même et l'appel des fonctions précédentes pour le bon déroulement du jeu.