#include "ListeChainee.h"
#include "define.h"
#include "enemies.h"
#include "libgraph.h"
#include "ship.h"
#include <SDL/SDL.h>
#include <stdlib.h>
#include <time.h>

list_t enemies;
list_t bombs = NULL;
list_t missiles = NULL;
entity_t ship;

int lives = 3;
int enemiesSpeed;

// Affiche l'ensemble des sprites du jeu
void draw()
{
    // Background
    rectanglePlein(0, 0, WIDTH, HEIGHT, 1);

    // Affichage des enemies et des bombes
    drawEnemies(enemies, bombs);

    // Affichage du vaisseau
    drawShip(ship, missiles, lives);

    // Mise à jour de la surface
    majSurface();
}

void init()
{

    creerSurface(WIDTH, HEIGHT, "Space Invaders");

    // Initialisation des enemies qui initialisent les bombes
    initEnemies(&enemies);

    // Initialisation du vaisseau qui initialise ses missiles
    initShip(&ship);

    // Initialisation du temps
    enemiesSpeed = 200;

    // Initialisation random
    srand(time(NULL));
}

void game()
{
    unsigned int tick = 0;
    int tick_enable = 1;
    int state = 1;
    int flySpeed = 10;
    SDL_Event event;
    while (state == 1) {
        // Test des  différents événements
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            state = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_RIGHT)
                moveShip_x(&ship, 1);
            if (event.key.keysym.sym == SDLK_LEFT)
                moveShip_x(&ship, -1);
            if (event.key.keysym.sym == SDLK_UP)
                shotShip(ship, &missiles);
            if (event.key.keysym.sym == SDLK_DOWN){
                if (tick_enable) {
                    tick_enable = 0;
                }else{
                    tick_enable = 1;
                }
            }
            break;
        }

        if (tick % flySpeed == 0) {
            updateBombs(&bombs, &ship, &lives);
            updateMissiles(&missiles, &enemies, &bombs);
        }
        if (tick % enemiesSpeed == 0) {
            updateEnemies(enemies, &bombs, &enemiesSpeed);
        }
        if (lives <= 0)
            state = 2;
        if (isWiningEnemies(enemies, ship))
            state = 2;
        if (enemies == NULL)
            state = 3;
        draw();
        if (tick_enable) tick++;
        SDL_Delay(1);
    }
    rectanglePlein(0, 0, WIDTH, HEIGHT, 1);
    majSurface();
    SDL_Delay(200);
    if (state == 2)
        printf("Vous avez Perdu !!!\n");
    else if (state == 3)
        printf("Vous avez Gagné !!!\n");
}

void quit()
{
    free_list(&enemies);
    free_list(&bombs);
    free_list(&missiles);
    fermerSurface();
}

int main()
{
    init();
    game();
    quit();
    return 0;
}
