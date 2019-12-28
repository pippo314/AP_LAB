#ifndef EQARR_H
#define EQARR_H

#include <stdio.h>
#include <stdlib.h>
#include "invArray.h"

#define MAX_OBJ 8

typedef struct tabEquip_t *equipArray_t;

equipArray_t newEquipArray();
void equipArray_add(equipArray_t equip, int obj); //chiamata nel main
void equipArray_remove(equipArray_t equip, int obj);
void equipArray_print(FILE *fp, equipArray_t equip, invArray_t invArray);
int equipArray_getDim(equipArray_t equip);
int equipArray_getByIndex(equipArray_t equipArray, int index);

#endif
