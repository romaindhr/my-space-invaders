#include "ListeChainee.h"
#include "libgraph.h"
#include <stdio.h>
#include <stdlib.h>

void head_push(list_t* pL, entity_t l)
{
    element_t* tmp;
    tmp = malloc(sizeof(element_t));
    tmp->entity = l;
    tmp->next = *pL;
    *pL = tmp;
}

int size(list_t l)
{
    int count = 0;
    while (l != NULL) {
        count++;
        l = l->next;
    }
    return count;
}

entity_t head_pop(list_t* pL)
{
    entity_t l;
    element_t* tmp;
    tmp = *pL;
    *pL = (*pL)->next;
    l = tmp->entity;
    free(tmp);
    return l;
}

void pop(list_t* pL, element_t* e)
{
    if ((*pL)->next == NULL || (*pL) == e)
        head_pop(pL);
    else {
        list_t tmp;
        if (*pL != NULL) {
            tmp = *pL;
            while (tmp->next != NULL && tmp->next != e) {
                tmp = tmp->next;
            }
            tmp->next = e->next;
            free(e);
        }
    }
}

void drawList(list_t l)
{
    list_t toPrint = l;
    while (toPrint != NULL) {
        entity_t e = toPrint->entity;
        afficherLutin(e.sprite, e.posx, e.posy);
        toPrint = toPrint->next;
    }
}

void free_list(list_t* pL)
{
    while (*pL != NULL) {
        head_pop(pL);
    }
}

void moveEntities_x(list_t entities, int dir, int step)
{
    while (entities != NULL) {
        entity_t* e = &(entities->entity);
        e->posx += (dir * step);
        entities = entities->next;
    }
}

void moveEntities_y(list_t entities, int dir, int step)
{
    while (entities != NULL) {
        entity_t* e = &(entities->entity);
        e->posy += (dir * step);
        entities = entities->next;
    }
}

// void updateEnemiesSpeed(list_t enemies, float boost){
//     while (enemies != NULL) {
//         entity_t *enemy = &(enemies->entity);
//         enemy->speed *= (-1 * boost);
//         enemies = enemies->next;
//     }
// }

void updateEntitiesSprite(list_t entities, int s)
{
    while (entities != NULL) {
        entity_t* e = &(entities->entity);
        e->sprite = s;
        entities = entities->next;
    }
}
