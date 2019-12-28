#ifndef PGLIST_H
#define PGLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "Pg.h"

typedef struct tabPg_t *pgList_t;

pgList_t newList();
void pgList_insert(pgList_t tabPg, pg_t pg);
void pgList_remove(pgList_t tabPg, PGkey key);
pg_t *pgList_searchByCode(pgList_t tabPg, PGkey key);
void listPrint(pgList_t l, invArray_t invArray);
void pgList_readFile(FILE *fp, pgList_t list);
#endif
