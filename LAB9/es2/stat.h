#include  <stdio.h>
#ifndef STAT_H
#define STAT_H

typedef struct {int hp,mp,atk,def,mag,spr;} stat_t;

stat_t scanStats(FILE *fp);
void showStats(FILE *fp, stat_t s);
void upgradeStats(stat_t *pg_stat, stat_t obj_stat);

#endif
