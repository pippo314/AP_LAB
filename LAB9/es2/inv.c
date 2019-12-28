#include "inv.h"

inv_t OBJscan(FILE *fp){
     inv_t obj;
     fscanf(fp, "%s %s", obj.name, obj.type);
     obj.stats = scanStats(fp);
     return obj;
}

void OBJshow(inv_t obj){
     printf("%s %s ", obj.name, obj.type);
     showStats(stdout, obj.stats);
     printf("\n");
}

int OBJcompare(inv_t o1, inv_t o2){
     return strcmp(o1.name, o2.name);
}

OBJkey OBJkeyGet(inv_t *o){
     return o->name;
}

int OBJkeyCompare(OBJkey k1, OBJkey k2){
     return strcmp(k1,k2);
}

inv_t OBJsetVoid(){
     inv_t obj;
     strcpy(obj.name, "_VOID");
     return obj;
}

stat_t OBJgetStat(inv_t *obj){
     return obj->stats;
}
