#ifndef __SHIP_H__
#define __SHIP_H__

#include "ListeChainee.h"

void initShip(entity_t* ship);
void drawShip(entity_t ship, list_t missiles, int lives);
void moveShip_x(entity_t* ship, int dir);
int isCollapsing(entity_t first, entity_t second);
void checkCollision(list_t* missiles, list_t* others_);
void updateMissiles(list_t* missiles, list_t* enemies, list_t* bombs);
void shotShip(entity_t ship, list_t* missiles);

#endif
