#include "equipArray.h"

struct tabEquip_t{
     int inUso, vettEq[MAX_OBJ];
};


equipArray_t newEquipArray(){
     equipArray_t equip = malloc(sizeof(struct tabEquip_t));
     equip->inUso=0;
     for (int i = 0; i < MAX_OBJ; i++) {
	  equip->vettEq[i]=-1;
     }
     return  equip;
}

void equipArray_add(equipArray_t equip, int obj){
     if (equip->inUso > MAX_OBJ) {
	  return; /* TODO: controllo rozzo */
     }
     equip->vettEq[equip->inUso++] = obj;
}

void equipArray_remove(equipArray_t equip, int obj){
     int i,j;
     for (i = 0; i < equip->inUso; i++) {
	  if (equip->vettEq[i] == obj){
	       for (j = i+1; j < equip->inUso; j++) {
		    equip->vettEq[j-1] = equip->vettEq[j];
	       }
	       equip->inUso--;
	  }
	  return; //escludo il caso in cui sia ammissibile avere più oggetti uguali
     }
}

void equipArray_print(FILE *fp, equipArray_t equip, invArray_t invArray){
     invArray_printObjs(equip->vettEq, equip->inUso,invArray);
}

int equipArray_getDim(equipArray_t equip){
     return equip->inUso;
}

int equipArray_getByIndex(equipArray_t equipArray, int index){
     return equipArray->vettEq[index];
}
