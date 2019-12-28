#ifndef CHAMPS_H
#define CHAMPS_H

#include "stats.h"
#include "inventory.h"


typedef struct {char code[MAXC], name[MAX_O], class[MAX_O]; tabEquip_t *equip; stat_t stats;} champ_t;

typedef struct {int isUsed; obj_t *equip[MAX_I];} tabEquip_t;

#endif
