#include "invArray.h"

static int MAXN=1;

struct  tabInv_t{
     inv_t *vettInv;
     int nInv, maxInv;
};
invArray_t newInvArray(){
     invArray_t tab=malloc(sizeof(struct tabInv_t));
     tab->vettInv=malloc(MAXN * sizeof(inv_t));
     tab->nInv=0;
     return tab;
}

void invArray_addObj(invArray_t tab, inv_t obj){
     if (tab->nInv == MAXN) {
	  MAXN = 2 * MAXN;
	  tab->vettInv = realloc(tab->vettInv, MAXN * sizeof(inv_t));
     }
     (tab->vettInv)[tab->nInv++] = obj;
}

int invArray_IndexOf(invArray_t tab, inv_t obj){
     int i;
     for (i = 0; i < tab->nInv; i++) {
	  if(OBJcompare(tab->vettInv[i], obj)==0)
	       return i;
     }
     return -1;
}

void printTab(invArray_t tab){
     int i;
     for (i = 0; i < tab->nInv; i++) {
	  OBJshow((tab->vettInv)[i]);
     }
}

void invArray_readFile(FILE *fp, invArray_t invArr){
     int dim, i;
     fscanf(fp, "%d", &dim);
     invArr->maxInv=dim;
     for (i = 0; i < dim; i++) {
	  invArray_addObj(invArr, OBJscan(fp));
     }
}

inv_t *invArray_searchByName(invArray_t tab, char *name){
     int i;
     for (i = 0; i < tab->nInv; i++) {
	  if(OBJkeyCompare(tab->vettInv[i].name, name)==0)
	       return &(tab->vettInv[i]);
     }
     return NULL;
}

void invArray_printObjs(int *indexes, int dim, invArray_t invArray){
     int i;
     for (i = 0; i < dim; i++) {
	  OBJshow(invArray->vettInv[indexes[i]]);
     }
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
     return &(invArray->vettInv[index]);
}
