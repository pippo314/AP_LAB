#include "pgList.h"

typedef struct node node_t, *link;

struct node {
     pg_t pg;
     link next;
};

struct tabPg_t {
     link headPg, tailPg;
     int nPg;
};

static link newNode(pg_t pg, link next){
     link x = malloc(sizeof(node_t));
     if (x == NULL)
	  return NULL;
     x->pg = pg;
     x->next=next;
     return x;
}

pgList_t newList(){
     pgList_t tab = malloc(sizeof(struct tabPg_t));
     tab->headPg=NULL;
     tab->nPg=0;
     tab->tailPg=NULL;
     return tab;
}


void pgList_insert(pgList_t tabPg, pg_t pg){
     tabPg->headPg=newNode(pg,tabPg->headPg);
     tabPg->nPg++;
}

void pgList_remove(pgList_t tabPg, PGkey key){
     link x, prev, h=tabPg->headPg;
     for(x=h, prev=NULL; x!=NULL; prev=x, x=x->next) {
	  if (PGkeyCompare(key, PGkeyGet(&x->pg))==0){
	       if(x==h)
		    h=x->next;
	       else
		    prev->next=x->next;
	       free(x);
	       tabPg->nPg--;
	       break;
	  }
     }
}

void listPrint(pgList_t l, invArray_t invArray){
     link x;
     int i;
     for ( x=l->headPg, i=0; i < l->nPg; x=x->next, i++) {
	  PGshow((x->pg), invArray);

     }
}

void pgList_readFile(FILE *fp, pgList_t list){
     int not_end=1;
     pg_t pg_tmp;
     while (not_end) {
	  pg_tmp = PGscan(fp);
	  if(!feof(fp)){ //se non è la fine del file aggiungi alla lista
	       pgList_insert(list, pg_tmp);
	  } else not_end = 0;
     }
}

pg_t *pgList_searchByCode(pgList_t tabPg, PGkey key){
     link *x;
     for (x = &tabPg->headPg; *x!=NULL; x = &((*x)->next)) {
	  if (PGkeyCompare(PGkeyGet(&((*x)->pg)), key) == 0)
	       return &((*x)->pg);
     }
     return NULL;
}
