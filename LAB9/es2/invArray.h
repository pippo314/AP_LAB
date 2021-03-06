#ifndef INVARR_H
#define INVARR_H

#include <stdio.h>
#include <stdlib.h>
#include "inv.h"

typedef struct tabInv_t *invArray_t;

invArray_t newInvArray();
void invArray_addObj(invArray_t tab, inv_t obj);
void printTab(invArray_t tab);
int invArray_IndexOf(invArray_t tab, inv_t obj);
void invArray_readFile(FILE *fp, invArray_t invArr);
inv_t *invArray_searchByName(invArray_t tab, char *name);
void invArray_printObjs(int *indexes, int dim, invArray_t invArray);
inv_t *invArray_getByIndex(invArray_t invArray, int index);
#endif
