#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "ListeChainee.h"

void initEnemies(list_t* enemies);
int isEdgingEnemies(list_t enemies);
void moveEnemies(list_t enemies, int* enemiesSpeed);
list_t pickAllowedEnemies(list_t enemies);
void shotEnemies(list_t enemies, list_t* bombs);
void updateEnemies(list_t enemies, list_t* bombs, int* enemiesSpeed);
void updateBombs(list_t* bombs, entity_t* ship, int* lives);
void drawEnemies(list_t enemies, list_t bombs);
int isWiningEnemies(list_t enemies, entity_t ship);

#endif
