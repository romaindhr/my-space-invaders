#ifndef __LISTECHAINEE_H__
#define __LISTECHAINEE_H__

typedef struct {
    int sprite;
    int posx;
    int posy;
    int width;
    int height;
} entity_t;

typedef struct _element {
    entity_t entity;
    struct _element* next;
} element_t, *list_t;

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
#endif
