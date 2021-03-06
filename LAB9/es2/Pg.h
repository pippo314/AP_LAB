#ifndef PG_H
#define PG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipArray.h"
#include "stat.h"

#define CODE 7
#define MAX_STR 50

typedef struct {
     char code[CODE], name[MAX_STR], class[MAX_STR];
     stat_t stat;
     equipArray_t equip;
} pg_t;
typedef char* PGkey;

void PGequip(pg_t *pg, int obj);
void PGunequip(pg_t *pg, int obj);
equipArray_t PGgetEquip(pg_t *pg);
pg_t PGscan(FILE *fp);
void PGshow(pg_t pg, invArray_t invArray);
PGkey PGkeyGet(pg_t *pg);
int PGkeyCompare(PGkey k1, PGkey k2);
pg_t PGsetVoid();
stat_t *PGgetStat(pg_t *pg);
void PGstatsEval(pg_t *pg, invArray_t invArray);

#endif
