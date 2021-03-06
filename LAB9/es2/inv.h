#ifndef INV_H
#define INV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stat.h"

#define MAX_STR 50

typedef struct {
     char name[MAX_STR], type[MAX_STR]; //suppongo che il nome sia la chiave
     stat_t stats;
} inv_t;
typedef char* OBJkey;

inv_t OBJscan(FILE *fp);
void OBJshow(inv_t obj);
int OBJcompare(inv_t o1, inv_t o2);
OBJkey OBJkeyGet(inv_t *o);
int OBJkeyCompare(OBJkey k1, OBJkey k2);
inv_t OBJsetVoid();
stat_t OBJgetStat(inv_t *obj);

#endif
