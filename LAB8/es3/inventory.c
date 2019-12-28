#include "inventory.h"

typedef struct {
     char name[MAX_O], type[MAX_O];
     stat_t stats;
} obj_t;

typedef struct {
     obj_t *objects;
     int nObj;
} inv_t;
