#include "enemies.h"
#include "define.h"
#include "libgraph.h"
#include "stdio.h"
#include "stdlib.h"
#define PROBASHOT 5
#define MINIMALSPEED 25

//  Sprite
int invader_monstre;
int invader_monstre2_1;
int invader_monstre2_2;
int invader_bombe;

int bombHeight;
int bombWidth;

int dir = 1;

int ENEMY_STEP;

void initEnemies(list_t* enemies)
{

    invader_monstre2_1 = chargerLutin("../Lutins/invader_monstre2_1.bmp", 1);
    invader_monstre2_2 = chargerLutin("../Lutins/invader_monstre2_2.bmp", 1);
    invader_bombe = chargerLutin("../Lutins/invader_bombe.bmp", 1);

    int enemyWidth;
    int enemyHeight;

    tailleLutin(invader_bombe, &bombWidth, &bombHeight);
    tailleLutin(invader_monstre2_1, &enemyWidth, &enemyHeight);

    *enemies = NULL;

    int row = 5;
    int col = 11;
    int diffx = 10;

    for (int i = 0; i < col * row; i++) {
        int offsetX = (WIDTH - (col * (enemyWidth + diffx)) + diffx) / 2;
        entity_t enemy = { .sprite = invader_monstre2_1,
            .posx = (i % col) * (enemyWidth + diffx) + offsetX,
            .posy = i / col * col * row + 150,
            .width = enemyWidth,
            .height = enemyHeight };
        head_push(enemies, enemy);
    }

    ENEMY_STEP = ((WIDTH / 2) - ((col / 2) * enemyWidth + (1 / 2) * enemyWidth + (col / 2) * diffx)) / 6;
}

int isEdgingEnemies(list_t enemies)
{
    while (enemies != NULL) {
        if (enemies->entity.posx + enemies->entity.width > WIDTH - 5 || enemies->entity.posx < 5)
            return 1;
        enemies = enemies->next;
    }
    return 0;
}

void moveEnemies(list_t enemies, int* enemiesSpeed)
{
    if (isEdgingEnemies(enemies)) {
        moveEntities_y(enemies, 1, ENEMY_STEP);
        dir *= -1;
        if (*enemiesSpeed > MINIMALSPEED)
            *enemiesSpeed -= 10;
        moveEntities_x(enemies, dir, ENEMY_STEP);
    } else {
        moveEntities_x(enemies, dir, ENEMY_STEP);
    }
}

list_t pickAllowedEnemies(list_t enemies)
{
    list_t allowedEnemies = NULL;
    list_t others = enemies;
    list_t toCheck = enemies;
    while (toCheck != NULL) {
        int flag = 0;
        while (others != toCheck) {
            if (toCheck->entity.posx == others->entity.posx) {
                flag = 1;
            }
            others = others->next;
        }
        if (!flag)
            head_push(&allowedEnemies, toCheck->entity);
        toCheck = toCheck->next;
        others = enemies;
    }
    return allowedEnemies;
}

void shotEnemies(list_t enemies, list_t* bombs)
{
    int flag = 1;
    list_t allowedEnemies = pickAllowedEnemies(enemies);
    while (allowedEnemies != NULL && flag) {
        entity_t* enemy = &(allowedEnemies->entity);
        if (rand() % 101 <= PROBASHOT) {
            entity_t bomb = { .sprite = invader_bombe,
                .posx = enemy->posx + (enemy->width / 2),
                .posy = enemy->posy + enemy->height,
                .width = bombWidth,
                .height = bombHeight };
            head_push(bombs, bomb);
            flag = 0;
        }
        allowedEnemies = allowedEnemies->next;
    }
}

// S'occupe de mettre à jour les enemies
void updateEnemies(list_t enemies, list_t* bombs, int* enemiesSpeed)
{

    shotEnemies(enemies, bombs);

    // Animation
    if (invader_monstre == invader_monstre2_1)
        invader_monstre = invader_monstre2_2;
    else
        invader_monstre = invader_monstre2_1;
    updateEntitiesSprite(enemies, invader_monstre);

    moveEnemies(enemies, enemiesSpeed);
}

void updateBombs(list_t* bombs, entity_t* ship, int* lives)
{
    moveEntities_y(*bombs, 1, 15);
    list_t toCheck;
    toCheck = *bombs;
    while (toCheck != NULL) {
        if (toCheck->entity.posy > HEIGHT - 20) {
            pop(bombs, toCheck);
        }
        if (toCheck->entity.posy + toCheck->entity.height > HEIGHT - (WIDTH / 20) && toCheck->entity.posx + toCheck->entity.width > ship->posx && toCheck->entity.posx < ship->posx + ship->width) {
            pop(bombs, toCheck);
            *lives -= 1;
        }
        toCheck = toCheck->next;
    }
}

void drawEnemies(list_t enemies, list_t bombs)
{
    drawList(enemies);
    drawList(bombs);
}

int isWiningEnemies(list_t enemies, entity_t ship)
{
    while (enemies != NULL) {
        if (enemies->entity.posy > ship.posy - ship.height)
            return 1;
        enemies = enemies->next;
    }
    return 0;
}
