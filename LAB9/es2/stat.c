#include "stat.h"
#include <stdio.h>
#include <stdlib.h>

//typedef struct {int hp,mp,atk,def,mag,spr;} stat_t;


stat_t scanStats(FILE *fp){
     stat_t s;
     fscanf(fp, "%d %d %d %d %d %d", &s.hp, &s.mp, &s.atk, &s.def, &s.mag, &s.spr);
     return s;
}

void showStats(FILE *fp, stat_t s){
     fprintf(fp, "%d %d %d %d %d %d", s.hp, s.mp, s.atk, s.def, s.mag, s.spr);
     /* TODO: se la statistica è minore di 1 stampa comunque 1 */
}

void upgradeStats(stat_t *pg_stat, stat_t obj_stat){
//     int i, nstat=6, tmp;
//     int *pg = &pg_stat->atk, *obj = &obj_stat.atk;
     pg_stat->atk+=obj_stat.atk;
     pg_stat->def+=obj_stat.def;
     pg_stat->hp+=obj_stat.hp;
     pg_stat->mag+=obj_stat.mag;
     pg_stat->mp+=obj_stat.mp;
     pg_stat->spr+=obj_stat.spr;
} /*itera la struct con un puntatore a intero, non funziona*/
