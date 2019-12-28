#include "Pg.h"

void PGequip(pg_t *pg, int obj){
     if (pg->equip == NULL)
	  pg->equip = newEquipArray();
     equipArray_add(pg->equip, obj);
}

equipArray_t PGgetEquip(pg_t *pg){
     return pg->equip;
}

pg_t PGscan(FILE *fp){
     pg_t pg;
     fscanf(fp, "%s %s %s", pg.code, pg.name, pg.class);
     pg.stat = scanStats(fp);
     pg.equip=NULL;
     return pg;
}

void PGshow(pg_t pg, invArray_t invArray){
     printf("%s %s %s ", pg.code, pg.name, pg.class);
     showStats(stdout, pg.stat);
     printf("\n");
     if(pg.equip != NULL){
	  printf("Equipaggiamento:\n");
	  equipArray_print(stdout, pg.equip, invArray);
     }
     printf("\n");
}

PGkey PGkeyGet(pg_t *pg) {
     return pg->code;
}

int PGkeyCompare(PGkey k1, PGkey k2){
     return strcmp(k1, k2);
}

pg_t PGsetVoid(){
     pg_t p;
     strcpy(p.code, "_VOID");
     return p;
}

void PGunequip(pg_t *pg, int obj){
     equipArray_remove(pg->equip, obj);
}

void PGstatsEval(pg_t *pg, invArray_t invArray){
     int i;
     for (i = 0; i < equipArray_getDim(pg->equip); i++) {
	  upgradeStats(PGgetStat(pg), OBJgetStat(invArray_getByIndex(invArray, equipArray_getByIndex(pg->equip, i))));
     }

}

stat_t *PGgetStat(pg_t *pg){
     return &(pg->stat);
}
