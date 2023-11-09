#include "ship.h"
#include "define.h"
#include "libgraph.h"
#include "stdio.h"

#define COOLDOWN 30
#define MISSILE_STEP 15

// Sprite
int invader_canon;
int invader_missile;

int timer = 0;

int missileWidth;
int missileHeight;

float SHIP_SPEED;

void initShip(entity_t* ship)
{

    invader_canon = chargerLutin("../Lutins/invader_canon.bmp", 1);
    invader_missile = chargerLutin("../Lutins/invader_missile.bmp", 1);

    int shipHeight;
    int shipWidth;

    tailleLutin(invader_canon, &shipWidth, &shipHeight);
    tailleLutin(invader_missile, &missileWidth, &missileHeight);

    ship->sprite = invader_canon;
    ship->posx = WIDTH / 2 - shipWidth / 2;
    ship->posy = HEIGHT - shipHeight - (HEIGHT / 20);
    ship->width = shipWidth;
    ship->height = shipHeight;

    SHIP_SPEED = WIDTH / 700;
}

void drawShip(entity_t ship, list_t missiles, int lives)
{
    // Affiche le vaisseau
    afficherLutin(ship.sprite, ship.posx, ship.posy);
    // Affiche les missiles
    drawList(missiles);
    // Affiche le cooldown de tir
    rectanglePlein(ship.posx, ship.posy + 30, timer * (ship.width / COOLDOWN), 5, 0);

    for (int i = 0; i < lives; i++) {
        afficherLutin(ship.sprite, i * 50, HEIGHT - (HEIGHT / 25));
    }
}

void moveShip_x(entity_t* ship, int dir)
{
    if ((dir == 1 && ship->posx + ship->width < WIDTH) || (dir == -1 && ship->posx > 0))
        ship->posx += (dir * SHIP_SPEED);
}

int isCollapsing(entity_t first, entity_t second)
{
    if (first.posy + first.height >= second.posy
        && first.posy + first.height <= second.posy + second.height
        && first.posx + first.width >= second.posx
        && first.posx <= second.posx + second.width) {
        return 1;
    }
    return 0;
}

void checkCollision(list_t* missiles, list_t* others_)
{
    list_t toCheck = *missiles;
    while (toCheck != NULL) {
        entity_t missile = toCheck->entity;
        list_t others = *others_;
        while (others != NULL) {
            entity_t other = others->entity;
            if (isCollapsing(missile, other)) {
                pop(missiles, toCheck);
                pop(others_, others);
            }
            others = others->next;
        }
        toCheck = toCheck->next;
    }
}

void updateMissiles(list_t* missiles, list_t* enemies, list_t* bombs)
{
    if (timer > 0)
        timer--;

    list_t toCheck = *missiles;
    while (toCheck != NULL) {
        entity_t missile = toCheck->entity;
        if (missile.posy < 0) {
            pop(missiles, toCheck);
        }
        toCheck = toCheck->next;
    }

    checkCollision(missiles, enemies);
    checkCollision(missiles, bombs);

    moveEntities_y(*missiles, -1, MISSILE_STEP);
}

void shotShip(entity_t ship, list_t* missiles)
{
    if (timer <= 0) {
        timer = COOLDOWN;
        entity_t missile = { .sprite = invader_missile,
            .posx = ship.posx + (ship.width / 2) - missileWidth / 2,
            .posy = ship.posy - ship.height + 10,
            .width = missileWidth,
            .height = missileHeight };
        head_push(missiles, missile);
    }
}
